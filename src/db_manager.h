// Database manager class for Lockbox.
//
//  // Example for how to create a new top_dir directory.
//  lockbox::DBManager::Options options;
//  options.type = lockbox::LockboxDatabase::TOP_DIR_META;
//  CreateGUIDString(&(options.name));
//  manager.Track(options);
//
//  string new_top_dir;
//  CreateGUIDString(&new_top_dir);
//  manager.Put(options, "name_key", "name_value");
//

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
    Options() : type(LockboxDatabase::UNKNOWN), name("") {}

    Options(LockboxDatabase::type type) : type(type), name("") {}

    Options(LockboxDatabase::type type, const string& name)
        : type(type), name(name) {}

    LockboxDatabase::type type;

    // Used by TopDir databases in order to locate the database.
    string name;
  };

  explicit DBManager(const string& db_location_base);

  virtual ~DBManager();

  bool Get(const Options& options, const string& key, string* value);

  bool Put(const Options& options, const string& key, const string& value);

  bool Track(const Options& options);

  uint64_t MaxID(const Options& options);

  uint64_t CountEntries(const Options& options);

 private:
  string db_location_base_;
  map<string, leveldb::DB*> db_map_;

  DISALLOW_COPY_AND_ASSIGN(DBManager);
};

} // namespace lockbox
