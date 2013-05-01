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
                                             Client* client)
    : dbm_(dbm),
      client_(client),
      thread_(new boost::thread(
          boost::bind(&FileEventQueueHandler::Run, this))),
      top_dir_id_(top_dir_id) {
  CHECK(dbm);
  CHECK(client);
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
  while (true) {
    // As new files become available, lock the cloud if necessary, and make any
    // necessary computations before sending up.

    leveldb::DB* db = dbm_->db(update_queue_options);
    it.reset(db->NewIterator(leveldb::ReadOptions()));
    it->SeekToFirst();
    if (!it->Valid()) {
      sleep(1);
      continue;
    }
    const string ts_path_key = it->key().ToString();
    const string event_type = it->value().ToString();
    vector<string> ts_path;
    // TODO(tierney): See the file_watcher_thread for updates to this code's
    // handling of the key formatting.
    base::SplitString(ts_path_key, ':', &ts_path);
    const string ts = ts_path[0];
    const string path = ts_path[1];

    // What to do in each of the |event_types| (added, deleted, modified)?
    // We'll start by handling the added case.
    int fw_action = 0;

    UserAuth user_auth;
    user_auth.email = "me2@you.com";
    user_auth.password = "password";

    base::StringToInt(event_type, &fw_action);
    PathLockRequest path_lock;
    PathLockResponse response;
    switch (fw_action) {
      case FW::Actions::Add:
        LOG(INFO) << "Read the file.";
        // Lock the file in the cloud.
        path_lock.user = user_auth;
        base::StringToInt64(top_dir_id_, &path_lock.top_dir_id);
        path_lock.rel_path = RemoveBaseFromInput(top_dir_path, path);

        client_->Exec<void, PathLockResponse&, const PathLockRequest&>(
            &LockboxServiceClient::AcquireLockRelPath,
            response,
            path_lock);
        if (!response.acquired) {
          LOG(INFO) << "Someone else already locked the file " << path;
          // Delete the entry?
          continue;
        }

        // Determine who it should be shared with.
        const vector<string>& users = response.users;

        // Read the file, do the encryption.
        RemotePackage package;
        Encryptor::Encrypt(path, users,
                           &(package.payload.data),
                           &(package.payload.user_enc_session));

        // Upload the package. Cloud needs to update the appropriate user's
        // update queues.
        int64 ret = client_->Exec<int64, const RemotePackage&>(
            &LockboxServiceClient::UploadPackage,
            package);

        // Release the lock.
        client_->Exec<void, const PathLockRequest&>(
            &LockboxServiceClient::ReleaseLockRelPath,
            path_lock);

        break;
      case FW::Actions::Delete:
        break;
      case FW::Actions::Modified:
        break;
      default:
        CHECK(false) << "Unrecognize event " << fw_action;
    }
  }
}

} // namespace lockbox
