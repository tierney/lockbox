#include "lockbox_service_handler.h"

#include "base/base64.h"
#include "base/sha1.h"
#include "base/strings/string_number_conversions.h"
#include "scoped_mutex.h"
#include "guid_creator.h"
#include "thrift_util.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>

using std::to_string;

namespace lockbox {

LockboxServiceHandler::LockboxServiceHandler(DBManagerServer* manager, Sync* sync)
    : manager_(manager), sync_(sync) {
  CHECK(manager);
}

void LockboxServiceHandler::RegisterUser(UserID& _return, const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterUser\n");

  DBManagerServer::Options options;
  options.type = ServerDB::EMAIL_USER;
  string value;
  manager_->Get(options, user.email, &value);
  if (!value.empty()) {
    LOG(INFO) << "User already registered " << user.email;
    _return = "";
    return;
  }

  _return = manager_->GetNextUserID();
  manager_->Put(options, user.email, _return);
  return;
}

void LockboxServiceHandler::RegisterDevice(DeviceID& _return,
                                           const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterDevice\n");
  DBManagerServer::Options options;
  options.type = ServerDB::EMAIL_USER;
  string user_id;
  manager_->Get(options, user.email, &user_id);
  if (user_id.empty()) {
    LOG(WARNING) << "User doesn't exist " << user.email;
    _return = "";
    return;
  }

  _return = manager_->GetNextDeviceID();

  // TODO(tierney): In the future, we can defensively check against an IP
  // address for an email account to throttle the accounts.
  options.type = ServerDB::USER_DEVICE;
  manager_->Append(options, user_id, _return);
}

bool LockboxServiceHandler::ShareTopDir(const UserAuth& user,
                                        const string& email,
                                        const TopDirID& top_dir_id) {
  LOG(INFO) << "ShareTopDir";
  // Authenticate.


  // Add the user from |email| (who |user| wants to share |top_dir_id| with) to
  // the list for |top_dir_id|.
  return manager_->AddEmailToTopDir(email, top_dir_id);
}

void LockboxServiceHandler::GetTopDirs(vector<TopDirID>& _return,
                                       const UserAuth& user) {
  // Authenticate.

  // Get the shared directories for the user.
  const UserID user_id(manager_->EmailToUserID(user.email));
  manager_->GetList(DBManager::Options(ServerDB::USER_TOP_DIR, ""),
                    user_id, &_return);
}

void LockboxServiceHandler::RegisterTopDir(TopDirID& top_dir_id,
                                           const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterTopDir\n");

  top_dir_id = manager_->GetNextTopDirID();

  // Appends the top_dir_id for the user to the end of the list of top dirs
  // owned by that user.
  UserID user_id(manager_->EmailToUserID(user.email));
  CHECK(manager_->Append(DBManager::Options(ServerDB::USER_TOP_DIR, ""),
                         user_id, top_dir_id));

  // TODO(tierney): Should create additional top_dir database here.
  CHECK(manager_->NewTopDir(
      DBManager::Options(ServerDB::TOP_DIR_PLACEHOLDER, top_dir_id)));

  // Update the editors for the top_dir.
  CHECK(manager_->Put(DBManager::Options(ServerDB::TOP_DIR_META, top_dir_id),
                      "EDITORS_" + user_id, user.email));
}

void LockboxServiceHandler::RegisterRelativePath(
    string& _return, const RegisterRelativePathRequest& req) {
  // If a request has been held, then must send back empty string.
  DBManagerServer::Options options;
  options.type = ServerDB::TOP_DIR_META;
  options.name = req.top_dir;

  // Lock access to the relative create lock for the tdn database.
  ScopedMutexLock lock(manager_->get_mutex(options));

  // Generate next number and send back the number.
  while (true) {
    string rel_path_id;
    CreateGUIDString(&rel_path_id);
    options.type = ServerDB::TOP_DIR_RELPATH;
    string found;
    manager_->Get(options, rel_path_id, &found);
    if (found.empty()) {
      manager_->Put(options, rel_path_id, "none");
      _return = rel_path_id;
      break;
    }
  }
  // TODO(tierney): If we find that two different GUIDs map to the same relative
  // path, then the users' app must reconcile by choosing the smallest GUID.
}


bool LockboxServiceHandler::AssociateKey(const UserAuth& user,
                                         const PublicKey& pub) {
  LOG(INFO) << "Associating " << user.email << " with "
            << string(pub.key.begin(), pub.key.end());
  string key;
  manager_->Get(DBManager::Options(ServerDB::EMAIL_KEY, ""),
                user.email, &key);
  if (!key.empty()) {
    LOG(WARNING) << "Overwriting keys";
  }

  manager_->Put(DBManager::Options(ServerDB::EMAIL_KEY, ""),
                user.email, pub.key);
  return true;
}

void LockboxServiceHandler::GetKeyFromEmail(PublicKey& _return,
                                            const string& email) {
  LOG(INFO) << "Looking up key for " << email;
  manager_->Get(DBManager::Options(ServerDB::EMAIL_KEY, ""), email,
                &(_return.key));
}

void LockboxServiceHandler::AcquireLockRelPath(PathLockResponse& _return,
                                               const PathLockRequest& lock) {
  // Your implementation goes here
  printf("LockRelPath\n");

  // TODO(tierney): Authenticate.

  // TODO(tierney): See if the lock is already held.
  DBManagerServer::Options options;
  options.type = ServerDB::TOP_DIR_RELPATH_LOCK;
  options.name = lock.top_dir;

  string lock_status;
  manager_->Get(options, lock.rel_path, &lock_status);

  // Set the lock.
  _return.acquired = true;

  // Get the names of the individuals with whom to share the directory.
  manager_->GetList(DBManager::Options(ServerDB::TOP_DIR_META, lock.top_dir),
                    "EDITORS", &(_return.users));

  // Send the data back in the response.
  return;
}

void LockboxServiceHandler::ReleaseLockRelPath(const PathLockRequest& lock) {
  printf("ReleaseLockRelPath");
}

int64_t LockboxServiceHandler::UploadPackage(const UserAuth& user,
                                             const RemotePackage& pkg) {
  // Your implementation goes here
  printf("UploadPackage\n");
  int64_t ret = pkg.payload.data.size();

  LOG(INFO) << "Received data (" << pkg.payload.data.size() << ") :"
            << pkg.rel_path_id;

  string mem;
  ThriftToString(pkg, &mem);
  LOG(INFO) << "Did it work?: " << mem.size();

  // Hash the input content.
  // TODO(tierney): This should actually be just the encrypted contents.
  const string& hash_of_prot = pkg.payload.data_sha1;

  // Associate the rel path GUID with the package. If the rel_path's latest is
  // empty then this is the first.
  DBManagerServer::Options options;
  options.name = pkg.top_dir;

  // TODO(tierney): Check that for the directory we have the correct GUID.

  // TODO(tierney): If we have a snapshot type, then we need to update the
  // latest snapshot order to include this hash.

  // Check if this is the first doc for the relpath.
  string previous;
  options.type = ServerDB::TOP_DIR_RELPATH;
  manager_->Get(options, pkg.rel_path_id, &previous);
  if (previous.empty()) {
    LOG(INFO) << "First upload for a file." << pkg.rel_path_id;
  }

  // Point the relpath's HEAD to this one.
  manager_->Put(options, pkg.rel_path_id, hash_of_prot);

  // Set the previous pointer to whatever previous is.
  options.type = ServerDB::TOP_DIR_FPTRS;
  manager_->Put(options, hash_of_prot, previous);

  // Write the file to disk.
  options.type = ServerDB::TOP_DIR_DATA;
  manager_->Put(options, hash_of_prot, mem);

  // TODO(tierney): Update the appropriate queues.
  options.type = ServerDB::UPDATE_ACTION_QUEUE;
  options.name = "";

  std::unique_lock<std::mutex> lock(sync_->db_mutex);
  manager_->Put(options,
                to_string(time(NULL)) + "_" + pkg.top_dir + "_" +
                pkg.rel_path_id + "_" + user.device + "_" +
                hash_of_prot,
                "");
  lock.unlock();
  LOG(INFO) << "Notifying the CV to wake someone up";
  sync_->cv.notify_one();

  return mem.size();
}

void LockboxServiceHandler::DownloadPackage(RemotePackage& _return,
                                            const DownloadRequest& req) {
  // Your implementation goes here
  printf("DownloadPackage\n");

  // Authenticate.

  // Get the package.
  string package_str;
  manager_->Get(DBManager::Options(ServerDB::TOP_DIR_DATA, req.top_dir),
            req.pkg_name, &package_str);

  RemotePackage package;
  ThriftFromString(package_str, &package);
  _return = package;
}

void LockboxServiceHandler::PollForUpdates(UpdateMap& _return,
                                           const UserAuth& auth,
                                           const DeviceID& device) {
  // TODO: authenticate.

  // Get the updates for the device and send back to the user. DEVICE_SYNC.
  DBManagerServer::Options options;
  options.type = ServerDB::DEVICE_SYNC;

  // TODO(tierney): This should be first or a list...
  LOG(INFO) << "Requesting updates for " << device;
  manager_->GetMap(options, device, &(_return.updates));
}

void LockboxServiceHandler::GetFptrs(vector<string>& _return,
                                     const UserAuth& auth,
                                     const string& top_dir,
                                     const string& hash) {
  // Authenticate.

  string prev;
  manager_->Get(DBManager::Options(ServerDB::TOP_DIR_FPTRS, top_dir),
                hash, &prev);
  _return.push_back(prev);
}

void LockboxServiceHandler::PersistedUpdates(const UserAuth& auth,
                                             const DeviceID& device,
                                             const UpdateList& updates) {
  LOG(INFO) << "Persisted updates.";
  // TODO: Need to grab lock on this database row.
  DBManagerServer::Options options;
  options.type = ServerDB::DEVICE_SYNC;
  for (const string& update : updates.updates) {
    manager_->Delete(options, update);
  }
}

void LockboxServiceHandler::Send(const UserAuth& sender,
                                 const std::string& receiver_email,
                                 const VersionInfo& vinfo) {
  // Your implementation goes here
  printf("Send\n");
}

void LockboxServiceHandler::GetLatestVersion(VersionInfo& _return,
                                             const UserAuth& requestor,
                                             const std::string& receiver_email) {
  // Your implementation goes here
  printf("GetLatestVersion\n");
}

} // namespace lockbox
