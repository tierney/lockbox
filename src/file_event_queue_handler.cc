#include "file_event_queue_handler.h"

#include "base/md5.h"
#include "base/strings/string_number_conversions.h"

namespace lockbox {

namespace {

// TODO(tierney): If memory becomes an issue, here is one place that can be
// improved. Incrementally read file and run contents through MD5 digest
// updater.
string FileToMD5(const string& path) {
  string contents;
  CHECK(base::ReadFileToString(path, &contents));
  return MD5String(contents);
}

} // namespace

FileEventQueueHandler::FileEventQueueHandler(const int top_dir_id ,
                                             DBManagerClient* dbm)
    : dbm_(dbm),
      thread_(new boost::thread(
          boost::bind(&FileEventQueueHandler::Run, this))),
      top_dir_id_(top_dir_id) {
}

FileEventQueueHandler::~FileEventQueueHandler() {
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
  CHECK(dbm_->Get(options, base::IntToString(top_dir_id_), &top_dir_path));

  file_util::FileEnumerator enumerator(
      FilePath(top_dir_path),
      true /* recursive */,
      file_util::FileEnumerator::FILES | file_util::FileEnumerator::DIRECTORIES);

  while (true) {
    base::FilePath fp(enumerator.Next());
    if (fp.value().empty()) {
      break;
    }
    file_util::FileEnumerator::FindInfo info;
    enumerator.GetFindInfo(&info);
    time_t mtime =
        file_util::FileEnumerator::GetLastModifiedTime(info).ToTimeT();
    path_mtime_[fp.value()] = base::IntToString(mtime);

    // TODO(tierney): This could be an epically slow operation.
    // Open up all files and hash them, mapping the path to the hash.
    path_hashes_[path] = FileToMD5(path);
  }


  DBManagerClient::Options
  while (true) {
    // As new files become available, lock the cloud if necessary, and make any
    // necessary computations before sending up.

  }
}

} // namespace lockbox
