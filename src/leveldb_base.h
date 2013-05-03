#pragma once

#include <string>

#include "leveldb/db.h"

using std::string;

namespace lockbox {

// Base class for inheritance that reduces boilerplate in the children classes.
class LevelDBBase {
 public:
  explicit LevelDBBase(const string& db_location);

  virtual ~LevelDBBase();

 protected:
  leveldb::DB* db_;
  string db_location_;
};

} // namespace lockbox
