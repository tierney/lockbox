#include "db_top_dir_meta.h"
#include "leveldb_util.h"
#include "base/stl_util.h"

namespace lockbox {

TopDirMetaDB::TopDirMetaDB(const string& db_location_base)
    : db_location_base_(db_location_base) {
}

TopDirMetaDB::~TopDirMetaDB() {
  STLDeleteContainerPairSecondPointers(top_dir_db_.begin(), top_dir_db_.end());
}

} // namespace lockbox
