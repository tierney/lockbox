#include "db_manager_client.h"

#include "leveldb_util.h"
namespace lockbox {

// TODO(tierney): Consider moving most of this activity to an init function
// outside the constructor.
DBManagerClient::DBManagerClient(const string& db_location_base)
    : DBManager(db_location_base, _ClientDB_VALUES_TO_NAMES) {
  // Initialize the databases and cache the mapping data that we have on disk.
  for (auto& iter : _ClientDB_VALUES_TO_NAMES) {
    ClientDB::type val = static_cast<ClientDB::type>(iter.first);
    if (val == ClientDB::UNKNOWN) {
      continue;
    }

    if (val >= ClientDB::TOP_DIR_PLACEHOLDER) {
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
}

DBManagerClient::~DBManagerClient() {
}

bool DBManagerClient::Get(const Options& options,
                          const string& key,
                          string* value) {
  CHECK(options.type != ClientDB::UNKNOWN);
  CHECK(options.type != ClientDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ClientDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  return DBManager::Get(options, key, value);
}

bool DBManagerClient::Put(const Options& options,
                          const string& key,
                          const string& value) {
  CHECK(options.type != ClientDB::UNKNOWN);
  CHECK(options.type != ClientDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ClientDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }

  return DBManager::Put(options, key, value);
}

bool DBManagerClient::Update(const Options& options,
                             const string& key,
                             const string& new_value) {
  CHECK(options.type != ClientDB::UNKNOWN);
  CHECK(options.type != ClientDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ClientDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
  return DBManager::Update(options, key, new_value);
}

bool DBManagerClient::NewTopDir(const Options& options) {
  CHECK(options.type == ClientDB::TOP_DIR_PLACEHOLDER);
  CHECK(!options.name.empty());
  Options new_options = options;
  for (auto& iter : _ClientDB_VALUES_TO_NAMES) {
    if (iter.first <= ClientDB::TOP_DIR_PLACEHOLDER) {
      continue;
    }
    new_options.type = iter.first;
    LOG(INFO) << "NewTopDir calling track for "
              << values_to_names_.find(new_options.type)->second
              << " " << new_options.name;
    // Call the function that setup up the database and store a pointer in the
    // appropriate places.
    CHECK(this->Track(new_options));
    LOG(INFO) << "Back from tracking...";
  }
}

string DBManagerClient::GenPath(const string& base, const Options& options) {
  return DBManager::GenPath(base, options);
}

string DBManagerClient::GenKey(const Options& options) {
  return DBManager::GenKey(options);
}

bool DBManagerClient::Track(const Options& options) {
  CHECK(options.type > ClientDB::TOP_DIR_PLACEHOLDER)
      << "Going to track "
      << _ClientDB_VALUES_TO_NAMES.find(options.type)->second;
  CHECK(!options.name.empty());

  return DBManager::Track(options);
}

uint64_t DBManagerClient::MaxID(const Options& options) {
  return DBManager::MaxID(options);
}

} // namespace lockbox
