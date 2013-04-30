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

namespace {

// Creates pathhs of the name /a/path/to/the/dest/THIS_IS_A_TYPE/OPTIONS_NAME.
string GenPath(const string& base, const DBManager::Options& options) {
  FilePath fp(base);
  string type_name = _ServerDB_VALUES_TO_NAMES.find(options.type)->second;
  LOG(INFO) << "GenPath() type_name " << type_name;
  FilePath appended_fp(fp.Append(type_name));
  if (!options.name.empty()) {
    return appended_fp.Append(options.name).value();
  }
  return appended_fp.value();
}

// Creates keys of the name THIS_IS_A_TYPE and THIS_IS_A_TYPEOPTIONS_NAME.
string GenKey(const DBManager::Options& options) {
  string key;
  key = _ServerDB_VALUES_TO_NAMES.find(options.type)->second;
  if (!options.name.empty()) {
    key.append(options.name);
  }
  return key;
}

} // namespace

DBManager::DBManager(const string& db_location_base)
    : db_location_base_(db_location_base) {
  // Setting the base database pointers.
  for (auto& iter : _ServerDB_VALUES_TO_NAMES) {
    ServerDB::type val = static_cast<ServerDB::type>(iter.first);

    if (val >= ServerDB::TOP_DIR_PLACEHOLDER) {
      break;
    }

    Options options;
    options.type = val;
    string key = GenKey(options);

    string path = GenPath(db_location_base, options);
    db_map_[key] = OpenDB(path);
  }

  // Set the counters for the ID-valued databases.
  num_users_.Set(MaxID(Options(ServerDB::EMAIL_USER)));
  num_devices_.Set(MaxID(Options(ServerDB::USER_DEVICE)));
  num_top_dirs_.Set(MaxID(Options(ServerDB::USER_TOP_DIR)));
}

DBManager::~DBManager() {
  STLDeleteContainerPairSecondPointers(db_map_.begin(), db_map_.end());
}

bool DBManager::Get(const Options& options,
                    const string& key,
                    string* value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key, value);
  return s.ok();
}

bool DBManager::Put(const Options& options,
                    const string& key,
                    const string& value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
  return s.ok();
}

bool DBManager::Update(const Options& options,
                       const string& key,
                       const string& new_value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
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
  CHECK(options.type == ServerDB::TOP_DIR_PLACEHOLDER);
  CHECK(!options.name.empty());
  Options new_options(options.type, options.name);
  for (auto& iter : _ServerDB_VALUES_TO_NAMES) {
    if (iter.first <= ServerDB::TOP_DIR_PLACEHOLDER) {
      continue;
    }
    new_options.type = static_cast<ServerDB::type>(iter.first);

    // Call the function that setup up the database and store a pointer in the
    // appropriate places.
    CHECK(Track(new_options));
  }
}

bool DBManager::Track(const Options& options) {
  CHECK(options.type > ServerDB::TOP_DIR_PLACEHOLDER)
      << _ServerDB_VALUES_TO_NAMES.find(options.type)->second;
  CHECK(!options.name.empty());

  string new_key = GenKey(options);
  CHECK(!ContainsKey(db_map_, new_key));
  db_map_[new_key] = OpenDB(GenPath(db_location_base_, options));
  return true;
}

uint64_t DBManager::MaxID(const Options& options) {
  CHECK(options.type == ServerDB::EMAIL_USER ||
        options.type == ServerDB::USER_DEVICE ||
        options.type == ServerDB::USER_TOP_DIR);
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

uint64_t DBManager::CountEntries(const Options& options) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  uint64_t count = 0;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    count++;
  }
  return count;
}

uint64_t DBManager::GetNextUserID() {
  return num_users_.Increment();
}

uint64_t DBManager::GetNextDeviceID() {
  return num_devices_.Increment();
}

uint64_t DBManager::GetNextTopDirID() {
  return num_top_dirs_.Increment();
}

} // namespace lockbox
