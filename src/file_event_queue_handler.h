#pragma once

#include <map>
#include <mutex>
#include <set>
#include <string>
#include <boost/thread/thread.hpp>

#include "client.h"
#include "db_manager_client.h"
#include "encryptor.h"

using std::map;
using std::mutex;
using std::set;
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
                                 Encryptor* encryptor,
                                 UserAuth* user_auth);

  virtual ~FileEventQueueHandler();

  void Run();

 private:
  void PrepareMaps();

  void HandleRemoteAction(const string& key, const string& value);
  void HandleRemoteAddAction(const string& timestamp,
                             const string& top_dir,
                             const string& top_dir_path,
                             const string& rel_path_guid,
                             const string& device,
                             const string& hash);
  void HandleRemoteModAction(const string& timestamp,
                             const string& top_dir,
                             const string& top_dir_path,
                             const string& rel_path_guid,
                             const string& rel_path,
                             const string& device,
                             const string& hash);

  void HandleLocalAction(const string& ts_path, const string& event_type);
  // Accompanying local action methods.
  bool HandleAddAction(const string& path);
  bool HandleModAction(const string& path);

  void SetIgnorableAction(const string& abs_path, const string& event_type);
  bool IgnorableAction(const string& abs_path, const string& event_type);

  DBManagerClient* dbm_;
  Client* client_;
  Encryptor* encryptor_;
  UserAuth* user_auth_;

  boost::thread* thread_;
  const string top_dir_id_;
  string top_dir_path_;

  set<string> ignorable_actions_;
  mutex ignorables_mutex_;

  map<string, string> path_hashes_;
  map<string, time_t> path_mtime_;
};

} // namespace lockbox
