#include "db_top_dir_meta.h"
#include "leveldb_util.h"
#include "base/stl_util.h"
#include "base/stringprintf.h"

namespace lockbox {

TopDirMetaDB::TopDirMetaDB(const string& db_location_base)
    : db_location_base_(db_location_base) {
}

TopDirMetaDB::~TopDirMetaDB() {
  STLDeleteContainerPairSecondPointers(top_dir_db_.begin(), top_dir_db_.end());
}

bool TopDirMetaDB::Track(const string& top_dir) {
  CHECK(!ContainsKey(top_dir_db_, top_dir));
  const string new_db_location =
      base::StringPrintf("%s/%s", db_location_base_.c_str(), top_dir.c_str());
  leveldb::DB* new_db = OpenDB(new_db_location);
  CHECK(new_db);
  top_dir_db_[top_dir] = new_db;
  return true;
}

leveldb::DB* TopDirMetaDB::GetTopDirDB(const string& top_dir) {
  auto iter = top_dir_db_.find(top_dir);
  if (iter == top_dir_db_.end()) {
    return NULL;
  }
  return iter->second;
}

} // namespace lockbox
