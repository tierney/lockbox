#include "db_device_sync.h"
#include "leveldb_util.h"

namespace lockbox {

DeviceSyncDB::DeviceSyncDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

DeviceSyncDB::~DeviceSyncDB() {
  delete db_;
}

} // namespace lockbox
