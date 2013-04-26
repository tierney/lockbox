#include "db_top_dir_meta.h"
#include "leveldb_util.h"

namespace lockbox {

TopDirMetaDB::TopDirMetaDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

TopDirMetaDB::~TopDirMetaDB() {
  delete db_;
}

} // namespace lockbox
