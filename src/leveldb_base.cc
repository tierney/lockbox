#include "leveldb_base.h"
#include "leveldb_util.h"

namespace lockbox {

LevelDBBase::LevelDBBase(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

LevelDBBase::~LevelDBBase() {
  delete db_;
}

} // namespace lockbox
