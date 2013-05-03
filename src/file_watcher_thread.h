#pragma once

#include <string>
#include <vector>

#include <boost/thread/thread.hpp>
#include <boost/bimap.hpp>

#include "db_manager_client.h"
#include "file_watcher/file_watcher.h"

using std::string;
using std::vector;

namespace lockbox {

class FileWatcherThread : public FW::FileWatchListener {
 public:
  // Does not take ownership of |db_manager|.
  FileWatcherThread(DBManagerClient* db_manager);

  virtual ~FileWatcherThread();

  void EnumerateDirectories(const string& path, vector<string>* dirs);

  void AddDirectory(const string& path, bool recursive);

  void RemoveDirectory(const string& path);

  void handleFileAction(FW::WatchID watchid, const string& dir,
                        const string& filename, FW::Action action);

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
