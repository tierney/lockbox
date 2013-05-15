#include "db_manager_client.h"

#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "leveldb_util.h"
#include "base/stl_util.h"
#include "scoped_mutex.h"

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

bool DBManagerClient::Append(const Options& options,
                             const string& key,
                             const string& new_value) {
  CHECK(options.type != ClientDB::UNKNOWN);
  CHECK(options.type != ClientDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ClientDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
  return DBManager::Append(options, key, new_value);
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
    CHECK(Track(new_options));
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

void DBManagerClient::Clean(const Options& options) {
  LOG(INFO) << "Cleaning database " << options.type << " for "
            << options.name;
  auto iter = db_map_.find(GenKey(options));
  CHECK(iter != db_map_.end());
  leveldb::DB* db = iter->second;
  scoped_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    Delete(options, it->key().ToString());
  }
}

string DBManagerClient::RelpathGuidToPath(const string& guid,
                                          const string& top_dir) {
  DBManager::Options options;
  options.type = ClientDB::RELPATH_ID_LOCATION;
  options.name = top_dir;

  string location;
  Get(options, guid, &location);
  // CHECK(!location.empty());

  return location;
}

bool DBManagerClient::AcquireLockPath(const string& guid,
                                      const string& top_dir) {
  const string path(RelpathGuidToPath(guid, top_dir));
  CHECK(!path.empty());
  LOG(INFO) << "AcquireLockPath " << path;

  if (!ContainsKey(path_locks_, path)) {
    LOG(INFO) << "Inserting path " << path;
    path_locks_.insert(make_pair(path, new mutex()));
  }

  ScopedMutexLock lock(path_locks_.at(path));

  // do something to the locked path.
  DBManager::Options options;
  options.type = ClientDB::RELPATH_LOCK;
  options.name = top_dir;

  string status;
  Get(options, path, &status);
  if (status == "LOCKED") {
    return false;
  }

  Put(options, path, "LOCKED");
  return true;
}

bool DBManagerClient::ReleaseLockPath(const string& guid,
                                      const string& top_dir) {
  const string path(RelpathGuidToPath(guid, top_dir));
  LOG(INFO) << "ReleaseLockPath " << path;

  LOG(INFO) << "Looking for path " << path;
  CHECK(ContainsKey(path_locks_, path));

  ScopedMutexLock lock(path_locks_.at(path));

  // do something to the locked path.
  DBManager::Options options;
  options.type = ClientDB::RELPATH_LOCK;
  options.name = top_dir;

  string status;
  Get(options, path, &status);
  CHECK(status == "LOCKED");
  CHECK(Delete(options, path));
  Put(options, path, "");
  Get(options, path, &status);
  CHECK(status.empty()) << status;
  return true;
}

TopDirID DBManagerClient::TopDirPathToID(const string& path) {
  TopDirID top_dir_id;
  Get(DBManager::Options(ClientDB::LOCATION_TOP_DIR, ""), path, &top_dir_id);
  return top_dir_id;
}

void DBManagerClient::NewRelPathGUIDLocalPath(const string& top_dir,
                                              const string& rel_path_guid,
                                              const string& rel_path) {
  CHECK(!top_dir.empty());
  CHECK(!rel_path.empty());
  CHECK(!rel_path_guid.empty());

  Options options;
  options.type = ClientDB::RELPATH_ID_LOCATION;
  options.name = top_dir;
  Put(options, rel_path_guid, rel_path);
  LOG(INFO) << "[" << top_dir << "] Mapped " << rel_path_guid << " : "
            << rel_path;

  options.type = ClientDB::LOCATION_RELPATH_ID;
  Put(options, rel_path, rel_path_guid);
}

bool DBManagerClient::AddNewFileToUnfilteredQueue(const string& dirname,
                                                  const string& filename,
                                                  const int action) {
  DBManagerClient::Options options;
  options.type = ClientDB::UNFILTERED_QUEUE;
  // TODO(tierney): Bring this key formation to somewhere more manageable. We
  // shouldn't bake this in... Also see file_event_queue_handler when updating
  // this code.
  const string key = base::StringPrintf("%s:%s/%s",
                                        std::to_string(time(NULL)).c_str(),
                                        dirname.c_str(),
                                        filename.c_str());
  LOG(INFO) << "Key: " << key;
  const string value = base::StringPrintf("%s/%s:%d",
                                          dirname.c_str(),
                                          filename.c_str(),
                                          action);
  LOG(INFO) << "Value: " << value;

  // Be sure to avoid overwriting a key that is already there.
  string existing_entry;
  Get(options, key, &existing_entry);
  if (!existing_entry.empty()) {
    LOG(INFO) << "Dropping duplicate event for " << key << " " << value;
    return false;
  }

  Put(options, key, value);
  return true;
}

} // namespace lockbox
