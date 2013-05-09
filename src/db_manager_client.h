#pragma once

#include <string>
#include <mutex>
#include <map>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"
#include "lockbox_types.h"
#include "counter.h"
#include "db_manager.h"

using std::string;
using std::mutex;
using std::map;

namespace lockbox {

class DBManagerClient : public DBManager {
 public:
  explicit DBManagerClient(const string& db_location_base);

  virtual ~DBManagerClient();

  bool Get(const Options& options, const string& key, string* value);

  bool Put(const Options& options, const string& key, const string& value);

  bool Append(const Options& options,
              const string& key,
              const string& new_value);

  bool NewTopDir(const Options& options);

  bool Track(const Options& options);

  uint64_t MaxID(const Options& options);

  // Creates pathhs of the name /a/path/to/the/dest/THIS_IS_A_TYPE/OPTIONS_NAME.
  string GenPath(const string& base, const Options& options);

  // Creates keys of the name THIS_IS_A_TYPE and THIS_IS_A_TYPEOPTIONS_NAME.
  string GenKey(const Options& options);

  void Clean(const Options& options);

  string RelpathGuidToPath(const string& guid, const string& top_dir);
  bool AcquireLockPath(const string& guid, const string& top_dir);
  bool ReleaseLockPath(const string& guid, const string& top_dir);

 private:
  map<string, mutex*> path_locks_;

  DISALLOW_COPY_AND_ASSIGN(DBManagerClient);
};

} // namespace lockbox
