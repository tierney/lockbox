#include "db_user_device.h"
#include "leveldb_util.h"

namespace lockbox {

UserDeviceDB::UserDeviceDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

UserDeviceDB::~UserDeviceDB() {
  delete db_;
}

} // namespace lockbox
