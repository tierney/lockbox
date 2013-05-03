#include "file_event_queue_handler.h"

#include <vector>

#include "base/md5.h"
#include "base/strings/string_number_conversions.h"
#include "base/memory/scoped_ptr.h"
#include "base/file_util.h"
#include "base/files/file_path.h"
#include "base/strings/string_split.h"
#include "file_watcher/file_watcher.h"
#include "util.h"
#include "encryptor.h"

using std::vector;

namespace lockbox {

namespace {

// TODO(tierney): If memory becomes an issue, here is one place that can be
// improved. Incrementally read file and run contents through MD5 digest
// updater.
string FileToMD5(const string& path) {
  string contents;
  CHECK(file_util::ReadFileToString(base::FilePath(path), &contents));
  return base::MD5String(contents);
}

} // namespace

FileEventQueueHandler::FileEventQueueHandler(const string& top_dir_id,
                                             DBManagerClient* dbm,
                                             Client* client,
                                             Encryptor* encryptor,
                                             UserAuth* user_auth)
    : dbm_(dbm),
      client_(client),
      encryptor_(encryptor),
      user_auth_(user_auth),
      thread_(new boost::thread(
          boost::bind(&FileEventQueueHandler::Run, this))),
      top_dir_id_(top_dir_id) {
  CHECK(dbm);
  CHECK(client);
  CHECK(encryptor);
  CHECK(user_auth);
  LOG(INFO) << "Starting FileEventQueueHandler for " << top_dir_id;
}

FileEventQueueHandler::~FileEventQueueHandler() {
}

// Enumerate the files and check the latest times. We can hold off on hashes
// until we have more information.
void FileEventQueueHandler::PrepareMaps(const string& top_dir_path) {
  file_util::FileEnumerator enumerator(
      base::FilePath(top_dir_path),
      true /* recursive */,
      file_util::FileEnumerator::FILES |
      file_util::FileEnumerator::DIRECTORIES);

  while (true) {
    base::FilePath fp(enumerator.Next());
    if (fp.value().empty()) {
      break;
    }

    file_util::FileEnumerator::FindInfo info;
    enumerator.GetFindInfo(&info);
    time_t mtime =
        file_util::FileEnumerator::GetLastModifiedTime(info).ToTimeT();
    path_mtime_[fp.value()] = mtime;

    // TODO(tierney): This could be an epically slow operation.
    // Open up all files and hash them, mapping the path to the hash.
    path_hashes_[fp.value()] = FileToMD5(fp.value());
  }
}

void FileEventQueueHandler::Run() {
  // Start up phase. Should get information from the RELPATHS to know which
  // files have been tracked already. Need to run through file to see if
  // anything has changed since last examined.

  // Enumerate the files and check the latest times. We can hold off on hashes
  // until we have more information.
  DBManagerClient::Options options;
  options.type = ClientDB::TOP_DIR_LOCATION;
  string top_dir_path;
  CHECK(dbm_->Get(options, top_dir_id_, &top_dir_path));
  PrepareMaps(top_dir_path);

  DBManagerClient::Options update_queue_options;
  update_queue_options.type = ClientDB::UPDATE_QUEUE_CLIENT;
  update_queue_options.name = top_dir_id_;
  scoped_ptr<leveldb::Iterator> it;
  leveldb::DB* db = dbm_->db(update_queue_options);
  while (true) {
    // As new files become available, lock the cloud if necessary, and make any
    // necessary computations before sending up.

    it.reset(db->NewIterator(leveldb::ReadOptions()));
    it->SeekToFirst();
    if (!it->Valid()) {
      sleep(1);
      continue;
    }
    const string ts_path_key = it->key().ToString();
    const string event_type = it->value().ToString();
    LOG(INFO) << "Got an action: " << ts_path_key << " " << event_type;
    vector<string> ts_path;
    // TODO(tierney): See the file_watcher_thread for updates to this code's
    // handling of the key formatting.
    LOG(INFO) << "ts_path_key: " << ts_path_key;
    base::SplitString(ts_path_key, ':', &ts_path);
    if (ts_path.size() != 2) {
      LOG(WARNING) << "bad ts_path_key " << ts_path_key;
      dbm_->Delete(update_queue_options, it->key().ToString());
      continue;
    }
    const string ts = ts_path[0];
    const string path = ts_path[1];

    // What to do in each of the |event_types| (added, deleted, modified)?
    // We'll start by handling the added case.
    int fw_action = 0;

    UserAuth user_auth;
    user_auth.email = "me2@you.com";
    user_auth.password = "password";

    base::StringToInt(event_type, &fw_action);
    LOG(INFO) << "fw_action: " << fw_action;
    bool success = false;
    switch (fw_action) {
      case FW::Actions::Add:
        success = HandleAddAction(top_dir_path, path);
        if (!success) {
          LOG(WARNING) << "Someone else won... ";
          CHECK(false);
        }
        // If not successful, consider rewriting the queue entry with the
        // current timestamp so that we can make sure to handle any updates to
        // the file, even if they come from the cloud.
        LOG(INFO) << "Done.";
        dbm_->Delete(update_queue_options, it->key().ToString());

        break;
      case FW::Actions::Delete:
        LOG(WARNING) << "Delete not implemented.";
        dbm_->Delete(update_queue_options, it->key().ToString());
        break;
      case FW::Actions::Modified:
        LOG(WARNING) << "Modified not implemented.";
        dbm_->Delete(update_queue_options, it->key().ToString());
        break;
      default:
        CHECK(false) << "Unrecognize event " << fw_action;
    }
  }
}

bool FileEventQueueHandler::HandleAddAction(const string& top_dir_path,
                                            const string& path) {

  // Lock the file in the cloud.
  PathLockRequest path_lock;
  path_lock.user.email = user_auth_->email;
  path_lock.user.password = user_auth_->password;
  path_lock.top_dir = top_dir_id_;
  path_lock.rel_path = RemoveBaseFromInput(top_dir_path, path);

  // Acquire the lock on the cloud.
  LOG(INFO) << "Locking on the cloud.";
  PathLockResponse response;
  client_->Exec<void, PathLockResponse&, const PathLockRequest&>(
      &LockboxServiceClient::AcquireLockRelPath,
      response,
      path_lock);
  if (!response.acquired) {
    LOG(INFO) << "Someone else already locked the file " << path;
    // TODO(tierney): Consider rewriting the queue entry with the current
    // timestamp so that we can make sure to handle any updates to the
    // file, even if they come from the cloud.
    return false;
  }

  // Read the file, do the encryption.
  LOG(INFO) << "Encrypting.";
  RemotePackage package;
  encryptor_->Encrypt(path, response.users,
                      &(package.payload.data),
                      &(package.payload.user_enc_session));

  string out_path;
  encryptor_->Decrypt(package.payload.data,
                      package.payload.user_enc_session,
                      &out_path);
  LOG(INFO) << "Is it what we expect? " << out_path;

  for (auto& ptr : package.payload.user_enc_session) {
    LOG(INFO) << "  " << ptr.first << " : " << ptr.second;
  }

  // Upload the package. Cloud needs to update the appropriate user's
  // update queues.
  LOG(INFO) << "Uploading.";
  int64 ret = client_->Exec<int64, const RemotePackage&>(
      &LockboxServiceClient::UploadPackage,
      package);
  LOG(INFO) << "  Uploaded " << ret;

  // Release the lock.
  LOG(INFO) << "Releasing lock";
  client_->Exec<void, const PathLockRequest&>(
      &LockboxServiceClient::ReleaseLockRelPath,
      path_lock);

  return true;
}

} // namespace lockbox
