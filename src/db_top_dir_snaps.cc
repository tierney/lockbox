#include "db_top_dir_snaps.h"
#include "leveldb_util.h"

namespace lockbox {

TopDirSnapsDB::TopDirSnapsDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

TopDirSnapsDB::~TopDirSnapsDB() {
  delete db_;
}

} // namespace lockbox
