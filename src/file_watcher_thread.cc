#include "file_watcher_thread.h"

namespace lockbox {

FileWatcherThread::FileWatcherThread(DBManagerClient* db_manager)
    : db_manager_(db_manager) {
}

FileWatcherThread::~FileWatcherThread() {
  delete updater_;
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
