#include "db_manager.h"
#include "lockbox_types.h"
#include "leveldb_util.h"

#include "base/files/file_path.h"
#include "base/stl_util.h"

using base::FilePath;

namespace lockbox {

namespace {

// Creates pathhs of the name /a/path/to/the/dest/THIS_IS_A_TYPE/OPTIONS_NAME.
string GenPath(const string& base, const DBManager::Options& options) {
  FilePath fp(base);
  fp.Append(_LockboxDatabase_VALUES_TO_NAMES.find(options.type)->second);
  if (!options.name.empty()) {
    fp.Append(options.name);
  }
  return fp.value();
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

DBManager::DBManager(const string& db_location)
    : db_location_base_(db_location) {

  for (auto& iter : _LockboxDatabase_VALUES_TO_NAMES) {
    LockboxDatabase::type val = static_cast<LockboxDatabase::type>(iter.first);

    if (val >= LockboxDatabase::TOP_DIR_PLACEHOLDER) {
      break;
    }

    Options options;
    options.type = val;
    string key = GenKey(options);

    db_map_[key] = OpenDB(GenPath(db_location, options));
  }
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

bool DBManager::Track(const Options& options) {
  string new_key = GenKey(options);
  CHECK(!ContainsKey(db_map_, new_key));
  db_map_[new_key] = OpenDB(GenPath(db_location_base_, options));
  return true;
}

} // namespace lockbox
