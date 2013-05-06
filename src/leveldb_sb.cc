#include <cassert>
#include <string>
#include "leveldb/db.h"

using std::string;
using std::to_string;

int main(int argc, char** argv) {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb_050613", &db);
  assert(status.ok());

  for (int i = 0; i < 10; i++) {
    string to_put("ZZZZ KEY");
    db->Put(leveldb::WriteOptions(), to_put + to_string(i), to_string(10 - i));
  }

  delete db;
  return 0;
}
