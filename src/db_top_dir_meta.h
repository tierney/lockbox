#pragma once

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"

using std::string;
using std::map;

namespace lockbox {

class TopDirMetaDB {
 public:
  explicit TopDirMetaDB(const string& db_location_base);

  virtual ~TopDirMetaDB();

  // Used to start tracking an appropriate database name. |top_dir| is appended
  // as a directory name to the |db_location_base_| for the location of the
  // tracked database.
  bool Track(const string& top_dir);

 private:
  // Get directory database.
  leveldb::DB* GetTopDirDB(const string& top_dir);

  // Database location used for connecting to leveldb.
  string db_location_base_;

  // Map between the top directory name and the database objects.
  map<string, leveldb::DB*> top_dir_db_;
};

} // namespace lockbox
