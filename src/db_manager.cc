#include "db_manager.h"
#include "lockbox_types.h"
#include "leveldb_util.h"

#include "base/files/file_path.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/stl_util.h"
#include "base/logging.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"

using base::FilePath;

namespace lockbox {

DBManager::DBManager(const string& db_location_base,
                     const map<int, const char*> values_to_names)
    : db_location_base_(db_location_base),
      values_to_names_(values_to_names) {
}

DBManager::~DBManager() {
  STLDeleteContainerPairSecondPointers(db_map_.begin(), db_map_.end());
}

bool DBManager::Get(const Options& options,
                    const string& key,
                    string* value) {
  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key, value);
  return s.ok();
}

bool DBManager::Put(const Options& options,
                    const string& key,
                    const string& value) {
  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
  return s.ok();
}

bool DBManager::Update(const Options& options,
                       const string& key,
                       const string& new_value) {
  leveldb::DB* db = db_map_.find(GenKey(options))->second;

  std::string value;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
  CHECK(s.ok() || s.IsNotFound());
  LOG(INFO) << "Update before " << value;
  if (!value.empty()) {
    value.append(",");
  }
  value.append(new_value);
  db->Put(leveldb::WriteOptions(), key, value);

  // TODO(tierney): Remove once we've tested the code.
  value.clear();
  s = db->Get(leveldb::ReadOptions(), key, &value);
  CHECK(s.ok());
  LOG(INFO) << "Update after " << value;
  return true;
}

bool DBManager::NewTopDir(const Options& options) {
  CHECK(false) << "Not implemented.";
  return false;
}

bool DBManager::Track(const Options& options) {
  string new_key = GenKey(options);
  CHECK(!ContainsKey(db_map_, new_key));
  db_map_[new_key] = OpenDB(GenPath(db_location_base_, options));
  return true;
}

uint64_t DBManager::MaxID(const Options& options) {
  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  uint64_t max = 0;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    uint64_t val = 0;
    std::vector<string> split;
    base::SplitString(it->value().ToString(), ',', &split);
    for (auto& iter : split) {
      if (iter.empty()) {
        continue;
      }
      CHECK(base::StringToUint64(iter, &val)) << iter << " "
                                              << it->value().ToString();
      if (max < val) {
        max = val;
      }
    }
  }
  return max;
}

string DBManager::GenPath(const string& base, const Options& options) {
  FilePath fp(base);
  auto found = values_to_names_.find(options.type);
  CHECK(found != values_to_names_.end());
  string type_name = found->second;
  LOG(INFO) << "GenPath() type_name " << type_name;
  FilePath appended_fp(fp.Append(type_name));
  if (!options.name.empty()) {
    return appended_fp.Append(options.name).value();
  }
  return appended_fp.value();
}

string DBManager::GenKey(const Options& options) {
  string key;
  LOG(INFO) << options.type;
  auto found = values_to_names_.find(options.type);
  CHECK(found != values_to_names_.end());
  key = found->second;
  if (!options.name.empty()) {
    key.append(options.name);
  }
  LOG(INFO) << "GenKey() " << key;
  return key;
}


} // namespace lockbox
