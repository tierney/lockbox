#include "leveldb_util.h"

#include "base/logging.h"

namespace lockbox {

leveldb::DB* OpenDB(const string& db_location) {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, db_location, &db);
  CHECK(status.ok());
  return db;
}

} // namespace lockbox
