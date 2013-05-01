#pragma once

#include <string>
#include <boost/thread/thread.hpp>

using std::string;

namespace lockbox {

// Will read from the UPDATE_QUEUE_CLIENT in order prepare files for upload. The
// package's relative path is locked by the client first. Then the package is
// prepared. If it appears that a path has been locked, then the client waits
// for the updates from the cloud before presenting a conflicting view to the
// end-user.
class FileEventQueueHandler {
 public:
  // Does not take ownership of |dbm|
  explicit FileEventQueueHandler(DBManagerClient* dbm);

  virtual ~FileEventQueueHandler();

  void Run();

 private:
  DBMangerClient* dbm_;
  boost::thread* thread_;
  int top_dir_id_;

  map<string, string> path_hashes_;
  map<string, time_t> path_mtime_;
};

} // namespace lockbox
