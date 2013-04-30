#include "file_watcher_thread.h"

#include "file_util.h"
#include "base/files/file_path.h"
#include "base/file_util.h"


namespace lockbox {

FileWatcherThread::FileWatcherThread(DBManagerClient* db_manager)
    : db_manager_(db_manager) {
}

FileWatcherThread::~FileWatcherThread() {
  delete updater_;
}

void FileWatcherThread::AddDirectory(const string& path, bool recursive) {
  file_watcher_.addWatch(path, this);
  if (!recursive) {
    return;
  }
  vector<string> sub_dirs;
  EnumerateDirectories(path, &sub_dirs);
  for (auto& sub_dir : sub_dirs) {
    AddDirectory(sub_dir, false);
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

void FileWatcherThread::handleFileAction(FW::WatchID watchid,
                                         const string& dir,
                                         const string& filename,
                                         FW::Action action) {
  base::FilePath potential_dir(base::FilePath(dir).Append(filename));
  switch(action) {
    case FW::Actions::Add:
      std::cout << "File (" << dir + "/" + filename << ") Added! " <<  std::endl;
      if (IsDirectory(potential_dir)) {
        LOG(INFO) << "Watching new directory.";
        AddDirectory(potential_dir.value(), true);
      }
      break;
    case FW::Actions::Delete:
      std::cout << "File (" << dir + "/" + filename << ") Deleted! " << std::endl;
      break;
    case FW::Actions::Modified:
      std::cout << "File (" << dir + "/" + filename << ") Modified! " << std::endl;
      break;
    default:
      std::cout << "Should never happen!" << std::endl;
  }
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
      sleep(1);
    }
  } catch (boost::thread_interrupted&) {
    return;
  } catch (std::exception& ) {
    return;
  }
}

} // namespace lockbox
