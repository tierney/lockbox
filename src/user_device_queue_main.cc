#include <cassert>
#include <string>

#include "leveldb/db.h"
#include "gflags/gflags.h"
#include "base/stringprintf.h"

using std::string;
using base::StringPrintf;

namespace lockbox {

string FormatUserDeviceKey(const string& user, const string& device) {
  return StringPrintf("%s_%s_ToFetch", user.c_str(), device.c_str());
}

class LevelDBMeditator {
 public:
  LevelDBMeditator() {

  }


 private:
  leveldb::DB* db;

};

} // namespace lockbox

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);

  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  return 0;
}
