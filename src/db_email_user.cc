#include "db_email_user.h"
#include "leveldb_util.h"

namespace lockbox {

EmailUserDB::EmailUserDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

EmailUserDB::~EmailUserDB() {
  delete db_;
}

string EmailUserDB::GetUser(const string& email) {
  string value;
  leveldb::Status s = db_->Get(leveldb::ReadOptions(), email, &value);
  return value;
}

bool EmailUserDB::SetEmailUser(const string& email, const string& user) {
  leveldb::Status s = db_->Put(leveldb::WriteOptions(), email, user);
  return true;
}

} // namespace lockbox
