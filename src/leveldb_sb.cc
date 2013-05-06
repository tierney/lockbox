#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"
#include "base/string_util.h"

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


  for (int i = 0; i < 10; i++) {
    string to_put("AAAA KEY");
    db->Put(leveldb::WriteOptions(), to_put + to_string(i), to_string(10 - i));
  }


  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->Seek("AAAA");
       it->Valid() && StartsWithASCII(it->key().ToString(), "AAAA", true);
       it->Next()) {
    std::cout << it->key().ToString() << std::endl;
  }

  delete db;
  return 0;
}
