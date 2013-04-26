#include "db_top_dir_fptrs.h"
#include "leveldb_util.h"

namespace lockbox {

TopDirFptrsDB::TopDirFptrsDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

TopDirFptrsDB::~TopDirFptrsDB() {
  delete db_;
}

} // namespace lockbox
