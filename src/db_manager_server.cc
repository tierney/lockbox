#include "db_manager_server.h"
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

DBManagerServer::DBManagerServer(const string& db_location_base)
    : DBManager(db_location_base, _ServerDB_VALUES_TO_NAMES) {

  // Setting the base database pointers.
  for (auto& iter : _ServerDB_VALUES_TO_NAMES) {
    ServerDB::type val = static_cast<ServerDB::type>(iter.first);
    if (val == ServerDB::UNKNOWN) {
      continue;
    }

    if (val >= ServerDB::TOP_DIR_PLACEHOLDER) {
      break;
    }

    Options options;
    LOG(INFO) << "Type to open " << val;
    options.type = val;
    string key = DBManager::GenKey(options);
    LOG(INFO) << "Type to open " << key;

    string path = DBManager::GenPath(db_location_base, options);
    db_map_[key] = OpenDB(path);

  }

  // Set the counters for the ID-valued databases.
  Options options;
  options.type = ServerDB::EMAIL_USER;
  num_users_.Set(MaxID(options));
  options.type = ServerDB::USER_DEVICE;
  num_devices_.Set(MaxID(options));
  options.type = ServerDB::USER_TOP_DIR;
  num_top_dirs_.Set(MaxID(options));
}

DBManagerServer::~DBManagerServer() {
}

bool DBManagerServer::Get(const Options& options,
                          const string& key,
                          string* value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  return DBManager::Get(options, key, value);
}

bool DBManagerServer::Put(const Options& options,
                          const string& key,
                          const string& value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  return DBManager::Put(options, key, value);
}

bool DBManagerServer::Update(const Options& options,
                             const string& key,
                             const string& new_value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
  return DBManager::Update(options, key, new_value);
}

bool DBManagerServer::NewTopDir(const Options& options) {
  CHECK(options.type == ServerDB::TOP_DIR_PLACEHOLDER);
  CHECK(!options.name.empty());
  Options new_options = options;
  for (auto& iter : _ServerDB_VALUES_TO_NAMES) {
    if (iter.first <= ServerDB::TOP_DIR_PLACEHOLDER) {
      continue;
    }
    new_options.type = iter.first;

    // TODO(tierney): Update the DBManagerServer's maps.

    // Call the function that setup up the database and store a pointer in the
    // appropriate places.
    CHECK(Track(new_options));
  }
}

bool DBManagerServer::Track(const Options& options) {
  CHECK(options.type > ServerDB::TOP_DIR_PLACEHOLDER)
      << _ServerDB_VALUES_TO_NAMES.find(options.type)->second;
  CHECK(!options.name.empty());

  db_mutex_[GetKey(options)] = new mutex();

  return DBManager::Track(options);
}

uint64_t DBManagerServer::MaxID(const Options& options) {
  CHECK(options.type == ServerDB::EMAIL_USER ||
        options.type == ServerDB::USER_DEVICE ||
        options.type == ServerDB::USER_TOP_DIR);
  return DBManager::MaxID(options);
}

string DBManagerServer::GenPath(const string& base, const Options& options) {
  return DBManager::GenPath(base, options);
}

string DBManagerServer::GenKey(const Options& options) {
  return DBManager::GenKey(options);
}

uint64_t DBManagerServer::GetNextUserID() {
  return num_users_.Increment();
}

uint64_t DBManagerServer::GetNextDeviceID() {
  return num_devices_.Increment();
}

uint64_t DBManagerServer::GetNextTopDirID() {
  return num_top_dirs_.Increment();
}

mutex* DBManagerServer::get_mutex(const Options& options) {
  string key(GenKey(options));
  auto ret_mutex = db_mutex_.find(key);
  CHECK(ret_mutex != db_mutex_.end());
  return ret_mutex->second;
}

} // namespace lockbox
