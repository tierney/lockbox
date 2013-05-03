#pragma once

#include <string>
#include <map>
#include <boost/thread/thread.hpp>

#include "client.h"
#include "db_manager_client.h"
#include "encryptor.h"

using std::map;
using std::string;

namespace lockbox {

// Will read from the UPDATE_QUEUE_CLIENT in order prepare files for upload. The
// package's relative path is locked by the client first. Then the package is
// prepared. If it appears that a path has been locked, then the client waits
// for the updates from the cloud before presenting a conflicting view to the
// end-user.
class FileEventQueueHandler {
 public:
  // Does not take ownership of |dbm| or |client|.
  explicit FileEventQueueHandler(const string& top_dir,
                                 DBManagerClient* dbm,
                                 Client* client,
                                 Encryptor* encryptor);

  virtual ~FileEventQueueHandler();

  void Run();

 private:
  void PrepareMaps(const string& top_dir_path);

  DBManagerClient* dbm_;
  Client* client_;
  Encryptor* encryptor_;
  boost::thread* thread_;
  const string top_dir_id_;

  map<string, string> path_hashes_;
  map<string, time_t> path_mtime_;
};

} // namespace lockbox
