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

UserID LockboxServiceHandler::RegisterUser(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterUser\n");

  DBManagerServer::Options options;
  options.type = ServerDB::EMAIL_USER;
  string value;
  manager_->Get(options, user.email, &value);
  if (!value.empty()) {
    LOG(INFO) << "User already registered " << user.email;
    return -1;
  }

  UserID uid = manager_->GetNextUserID();
  string uid_to_persist = base::IntToString(uid);
  manager_->Put(options, user.email, uid_to_persist);
  return uid;
}

DeviceID LockboxServiceHandler::RegisterDevice(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterDevice\n");
  DBManagerServer::Options options;
  options.type = ServerDB::EMAIL_USER;
  string user_id;
  manager_->Get(options, user.email, &user_id);
  if (user_id.empty()) {
    LOG(WARNING) << "User doesn't exist " << user.email;
    return -1;
  }

  DeviceID device_id = manager_->GetNextDeviceID();
  string device_id_to_persist = base::IntToString(device_id);

  // TODO(tierney): In the future, we can defensively check against an IP
  // address for an email account to throttle the accounts.
  options.type = ServerDB::USER_DEVICE;
  manager_->Append(options, user_id, device_id_to_persist);

  // With GUID approach, we don't need this anymore.
  // options.type = ServerDB::DEVICE_SYNC;
  // manager_->Put(options, device_id_to_persist, "");

  return device_id;
}

TopDirID LockboxServiceHandler::RegisterTopDir(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterTopDir\n");

  const TopDirID top_dir_id = manager_->GetNextTopDirID();
  const string top_dir_id_to_persist = base::IntToString(top_dir_id);

  // Appends the top_dir_id for the user to the end of the list of top dirs
  // owned by that user.
  DBManagerServer::Options options;
  options.type = ServerDB::USER_TOP_DIR;
  CHECK(manager_->Append(options, user.email, top_dir_id_to_persist));

  // TODO(tierney): Should create additional top_dir database here.
  options.type = ServerDB::TOP_DIR_PLACEHOLDER;
  options.name = top_dir_id_to_persist;
  CHECK(manager_->NewTopDir(options));

  // Get the EMAIL_USER user.
  options.type = ServerDB::EMAIL_USER;
  options.name = "";

  string user_id;
  CHECK(manager_->Get(options, user.email, &user_id));

  // Update the editors for the top_dir.
  options.type = ServerDB::TOP_DIR_META;
  options.name = top_dir_id_to_persist;
  string guid;
  CreateGUIDString(&guid);
  CHECK(manager_->Put(options, "EDITORS_" + guid, user_id));

  return top_dir_id;
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

  return true;
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
  _return.users.push_back("me2@you.com");

  // Send the data back in the response.
  return;
}

void LockboxServiceHandler::ReleaseLockRelPath(const PathLockRequest& lock) {
  printf("ReleaseLockRelPath");
}

int64_t LockboxServiceHandler::UploadPackage(const RemotePackage& pkg) {
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
  const string sha1 = base::SHA1HashString(pkg.payload.data);
  const string hash_of_prot = base::HexEncode(sha1.c_str(), sha1.size());

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
                pkg.rel_path_id + "_" + hash_of_prot,
                "");
  lock.unlock();
  LOG(INFO) << "Notifying the CV to wake someone up";
  sync_->cv.notify_one();

  return mem.size();
}

void LockboxServiceHandler::DownloadPackage(LocalPackage& _return,
                                            const DownloadRequest& req) {
  // Your implementation goes here
  printf("DownloadPackage\n");
}

void LockboxServiceHandler::PollForUpdates(UpdateList& _return,
                                           const UserAuth& auth,
                                           const DeviceID device) {
  // TODO: authenticate.

  // Get the updates for the device and send back to the user. DEVICE_SYNC.
  DBManagerServer::Options options;
  options.type = ServerDB::DEVICE_SYNC;
  manager_->Get(options, std::to_string(device), &(_return.updates));
}

void LockboxServiceHandler::PersistedUpdates(const UserAuth& auth,
                                             const DeviceID device,
                                             const UpdateList& updates) {
  LOG(INFO) << "Persisted updates.";
  // TODO: Need to grab lock on this database row.
  DBManagerServer::Options options;
  options.type = ServerDB::DEVICE_SYNC;
  string db_updates;
  manager_->Get(options, std::to_string(device), &db_updates);
  db_updates.erase(0, updates.updates.size());
  manager_->Put(options, std::to_string(device), db_updates);
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
