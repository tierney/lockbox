#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"

using std::string;

namespace lockbox {

class EmailKeyDB {
 public:
  explicit EmailKeyDB(const string& db_location);

  virtual ~EmailKeyDB();

 private:
  // Pointer the database. Must be deleted when we destroy this context.
  leveldb::DB* db_;

  // Database location used for connecting to leveldb.
  string db_location_;
};

} // namespace lockbox
