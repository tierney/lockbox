#include "db_top_dir_data.h"
#include "leveldb_util.h"

namespace lockbox {

TopDirDataDB::TopDirDataDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

TopDirDataDB::~TopDirDataDB() {
  delete db_;
}

} // namespace lockbox
