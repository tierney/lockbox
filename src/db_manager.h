#pragma once

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"
#include "lockbox_types.h"

using std::map;
using std::string;

namespace lockbox {

class DBManager {
 public:
  struct Options {
    LockboxDatabase::type type;

    // Used by TopDir databases in order to locate the database.
    string name;
  };

  explicit DBManager(const string& db_location);

  virtual ~DBManager();

  bool Get(const Options& options, const string& key, string* value);

  bool Put(const Options& options, const string& key, const string& value);

  bool Track(const Options& options);

 private:
  string db_location_base_;
  map<string, leveldb::DB*> db_map_;
};

} // namespace lockbox
