#pragma once

#include <string>
#include <boost/thread/thread.hpp>
#include <boost/bimap.hpp>

#include "db_manager_client.h"
#include "file_watcher/file_watcher.h"

using std::string;

namespace lockbox {

class FileWatcherThread {
 public:
  // Does not take ownership of |db_manager|.
  FileWatcherThread(DBManagerClient* db_manager);

  virtual ~FileWatcherThread();

  void AddDirectory(const string& path);

  void RemoveDirectory(const string& path);

  void Start();
  void Stop();
  void Join();
  void Run();

 private:
  boost::thread* updater_;
  DBManagerClient* db_manager_;
  FW::FileWatcher file_watcher_;
  boost::bimap<FW::WatchID, string> watch_path_bimap_;
};

} // namespace lockbox
