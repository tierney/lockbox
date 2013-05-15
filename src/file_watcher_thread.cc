#include "file_watcher_thread.h"

#include <unistd.h>
#include "file_util.h"
#include "base/files/file_path.h"
#include "base/file_util.h"
#include "db_manager_client.h"
#include "base/strings/string_number_conversions.h"
#include "base/stringprintf.h"

namespace lockbox {

const int kNumAttempts = 3;

FileWatcherThread::FileWatcherThread(DBManagerClient* db_manager)
    : db_manager_(db_manager) {
}

FileWatcherThread::~FileWatcherThread() {
  delete updater_;
}

void FileWatcherThread::AddDirectory(const string& path, bool recursive) {
  file_watcher_.addWatch(path, this);

  // Should enumerate all files for the directory and then add these to the
  // queue.
  // TODO
  vector<string> files;
  EnumerateFiles(path, &files);
  for (const string& abs_filepath : files) {
    LOG(INFO) << "Adding file " << abs_filepath;
    base::FilePath filepath(abs_filepath);
    db_manager_->AddNewFileToUnfilteredQueue(filepath.DirName().value(),
                                             filepath.BaseName().value(),
                                             FW::Action::Add);
  }

  if (!recursive) {
    return;
  }

  vector<string> sub_dirs;
  EnumerateDirectories(path, &sub_dirs);
  for (auto& sub_dir : sub_dirs) {
    AddDirectory(sub_dir, false);
  }
}

void FileWatcherThread::EnumerateFiles(const string& directory,
                                       vector<string>* files) {
  CHECK(files);
  base::FilePath base(directory);
  CHECK(base.IsAbsolute());

  file_util::FileEnumerator enumerator(
      base,
      false /* recursive */,
      file_util::FileEnumerator::FILES);
  while (true) {
    base::FilePath fp(enumerator.Next());
    if (fp.value().empty()) {
      break;
    }
    files->push_back(fp.value());

    file_util::FileEnumerator::FindInfo info;
    enumerator.GetFindInfo(&info);
    if (file_util::FileEnumerator::IsDirectory(info)) {
      CHECK(false) << "Got a directory when asking for files only";
    }
  }
}


void FileWatcherThread::EnumerateDirectories(const string& path,
                                             vector<string>* dirs) {
  CHECK(dirs);
  base::FilePath base(path);
  CHECK(base.IsAbsolute());

  file_util::FileEnumerator enumerator(
      base,
      true /* recursive */,
      file_util::FileEnumerator::FILES | file_util::FileEnumerator::DIRECTORIES);
  while (true) {
    base::FilePath fp(enumerator.Next());
    if (fp.value().empty()) {
      break;
    }
    file_util::FileEnumerator::FindInfo info;
    enumerator.GetFindInfo(&info);
    if (file_util::FileEnumerator::IsDirectory(info)) {
      dirs->push_back(fp.value());
    }
  }
}

namespace {

bool IgnorableFile(const string& filename) {
  // swp, swpx, or . files
  (void) filename;
  return true;
}

} // namespace

void FileWatcherThread::handleFileAction(FW::WatchID watchid,
                                         const string& dir,
                                         const string& filename,
                                         FW::Action action) {
  (void) watchid;

  base::FilePath potential_dir(base::FilePath(dir).Append(filename));

  int i = 0;
  bool is_dir = false;
  switch(action) {
    case FW::Actions::Add:
      std::cout << "File (" << dir + "/" + filename << ") Added! "
                << std::endl;
      // There are problems with getting inotify updates without a file to look
      // at.
      for (i = 0; i < kNumAttempts; i++) {
        if (!IsDirectory(potential_dir, &is_dir)) {
          LOG(WARNING) << "Something broke about the file. Just ignore for now.";
          sleep(1);
          continue;
        } else {
          break;
        }
      }
      if (i == kNumAttempts) {
        LOG(WARNING) << "Dropping file: " << dir << "/" << filename;
      }

      if (is_dir) {
        LOG(INFO) << "Watching new directory " << potential_dir.value();
        AddDirectory(potential_dir.value(), true);
        LOG(INFO) << "Do not 'upload' a directory itself.";
        return;
      }
      break;
    case FW::Actions::Delete:
      std::cout << "File (" << dir + "/" + filename << ") Deleted! "
                << std::endl;
      break;
    case FW::Actions::Modified:
      std::cout << "File (" << dir + "/" + filename << ") Modified! "
                << std::endl;
      break;
    default:
      CHECK(false) << "Should never happen!";
  }
  /*
  DBManagerClient::Options options;
  options.type = ClientDB::UNFILTERED_QUEUE;
  // TODO(tierney): Bring this key formation to somewhere more manageable. We
  // shouldn't bake this in... Also see file_event_queue_handler when updating
  // this code.
  const string key = base::StringPrintf("%s:%s/%s",
                                        base::Int64ToString(time(NULL)).c_str(),
                                        dir.c_str(),
                                        filename.c_str());
  LOG(INFO) << "Key: " << key;
  const string value = base::StringPrintf("%s/%s:%d",
                                          dir.c_str(),
                                          filename.c_str(),
                                          action);
  LOG(INFO) << "Value: " << value;

  // Be sure to avoid overwriting a key that is already there.
  string existing_entry;
  db_manager_->Get(options, key, &existing_entry);
  if (!existing_entry.empty()) {
    LOG(INFO) << "Dropping duplicate event for " << key << " " << value;
    return;
  }

  db_manager_->Put(options, key, value);
  */
  db_manager_->AddNewFileToUnfilteredQueue(dir, filename, action);
}

void FileWatcherThread::Start() {
  updater_ = new boost::thread(boost::bind(&FileWatcherThread::Run, this));
}

void FileWatcherThread::Stop() {
  updater_->interrupt();
}

void FileWatcherThread::Join() {
  updater_->join();
}

void FileWatcherThread::Run() {
  try {
    while (true) {
      file_watcher_.update();
      boost::this_thread::interruption_point();
      usleep(100000);
    }
  } catch (boost::thread_interrupted&) {
    return;
  } catch (std::exception& ) {
    return;
  }
}

} // namespace lockbox
