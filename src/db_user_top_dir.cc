#include "db_user_top_dir.h"
#include "leveldb_util.h"

namespace lockbox {

UserTopDirDB::UserTopDirDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

UserTopDirDB::~UserTopDirDB() {
  delete db_;
}

} // namespace lockbox
