#include "db_top_dir_relpath_lock.h"
#include "leveldb_util.h"

namespace lockbox {

TopDirRelpathLockDB::TopDirRelpathLockDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

TopDirRelpathLockDB::~TopDirRelpathLockDB() {
  delete db_;
}

} // namespace lockbox
