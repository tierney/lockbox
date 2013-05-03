#include "db_email_key.h"
#include "leveldb_util.h"

namespace lockbox {

EmailKeyDB::EmailKeyDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

EmailKeyDB::~EmailKeyDB() {
  delete db_;
}

} // namespace lockbox
