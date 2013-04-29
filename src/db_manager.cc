#include "db_manager.h"
#include "lockbox_types.h"
#include "leveldb_util.h"

#include "base/files/file_path.h"
#include "base/stl_util.h"
#include "base/logging.h"

using base::FilePath;

namespace lockbox {

namespace {

// Creates pathhs of the name /a/path/to/the/dest/THIS_IS_A_TYPE/OPTIONS_NAME.
string GenPath(const string& base, const DBManager::Options& options) {
  FilePath fp(base);
  string type_name = _LockboxDatabase_VALUES_TO_NAMES.find(options.type)->second;
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
  key = _LockboxDatabase_VALUES_TO_NAMES.find(options.type)->second;
  if (!options.name.empty()) {
    key.append(options.name);
  }
  return key;
}

} // namespace

DBManager::DBManager(const string& db_location_base)
    : db_location_base_(db_location_base) {

  for (auto& iter : _LockboxDatabase_VALUES_TO_NAMES) {
    LockboxDatabase::type val = static_cast<LockboxDatabase::type>(iter.first);

    if (val >= LockboxDatabase::TOP_DIR_PLACEHOLDER) {
      break;
    }

    Options options;
    options.type = val;
    string key = GenKey(options);

    string path = GenPath(db_location_base, options);
    db_map_[key] = OpenDB(path);
  }
}

DBManager::~DBManager() {
  STLDeleteContainerPairSecondPointers(db_map_.begin(), db_map_.end());
}

bool DBManager::Get(const Options& options,
                    const string& key,
                    string* value) {
  CHECK(options.type != LockboxDatabase::UNKNOWN);
  CHECK(options.type != LockboxDatabase::TOP_DIR_PLACEHOLDER);
  if (options.type > LockboxDatabase::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key, value);
  return s.ok();
}

bool DBManager::Put(const Options& options,
                    const string& key,
                    const string& value) {
  CHECK(options.type != LockboxDatabase::UNKNOWN);
  CHECK(options.type != LockboxDatabase::TOP_DIR_PLACEHOLDER);
  if (options.type > LockboxDatabase::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  leveldb::DB* db = db_map_.find(GenKey(options))->second;
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
  return s.ok();
}

bool DBManager::Track(const Options& options) {
  CHECK(options.type > LockboxDatabase::TOP_DIR_PLACEHOLDER);
  CHECK(!options.name.empty());

  string new_key = GenKey(options);
  CHECK(!ContainsKey(db_map_, new_key));
  db_map_[new_key] = OpenDB(GenPath(db_location_base_, options));
  return true;
}

uint64_t DBManager::CountEntries(const Options& options) {
  CHECK(options.type != LockboxDatabase::UNKNOWN);
  CHECK(options.type != LockboxDatabase::TOP_DIR_PLACEHOLDER);
  if (options.type > LockboxDatabase::TOP_DIR_PLACEHOLDER) {
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

} // namespace lockbox
