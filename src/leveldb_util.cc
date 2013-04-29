#include "leveldb_util.h"

#include "base/logging.h"
#include "base/file_util.h"

namespace lockbox {

leveldb::DB* OpenDB(const string& db_location) {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;

  CHECK(file_util::CreateDirectory(base::FilePath(db_location)));

  leveldb::Status status = leveldb::DB::Open(options, db_location, &db);
  CHECK(status.ok()) << "Status was " <<  status.ToString();
  return db;
}

} // namespace lockbox
