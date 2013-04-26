#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"

using std::string;

namespace lockbox {

class EmailUserDB {
 public:
  // |db_location| is the full path to the directory that names the leveldb
  // database.
  explicit EmailUserDB(const string& db_location);

  virtual ~EmailUserDB();

  string GetUser(const string& email);

  bool SetEmailUser(const string& email, const string& user);

 private:
  // Database location used for connecting to leveldb.
  const string db_location_;

  // Pointer the database. Must be deleted when we destroy this context.
  leveldb::DB* db_;

  DISALLOW_COPY_AND_ASSIGN(EmailUserDB);
};

} // namespace lockbox
