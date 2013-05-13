#include "db_manager_server.h"

#include <set>
#include <vector>

#include "lockbox_types.h"
#include "leveldb_util.h"

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/stl_util.h"
#include "base/logging.h"
#include "guid_creator.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"

using base::FilePath;
using std::set;
using std::vector;

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

  InitTopDirs();

  // Set the counters for the ID-valued databases.
  Options options;
  options.type = ServerDB::USER_DEVICE;
  num_devices_.Set(MaxID(options));
}

DBManagerServer::~DBManagerServer() {
}

void DBManagerServer::InitTopDirs() {
  // Iterate through all of the USER_TOP_DIR profiles and cache the top_dir
  // information in a set. Then we prime the appropriate maps with the keys for
  // the top_dirs.
  Options user_top_dir_options;
  user_top_dir_options.type = ServerDB::USER_TOP_DIR;

  leveldb::DB* db = DBManager::db(user_top_dir_options);
  scoped_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));

  set<string> top_dirs;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    vector<string> user_top_dirs;
    base::SplitString(it->value().ToString(), ',', &user_top_dirs);
    for (const string& top_dir_val : user_top_dirs) {
      top_dirs.insert(top_dir_val);
    }
  }

  Options new_top_dir_options;
  new_top_dir_options.type = ServerDB::TOP_DIR_PLACEHOLDER;
  for (const string& iter : top_dirs) {
    new_top_dir_options.name = iter;
    NewTopDir(new_top_dir_options);
  }
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

bool DBManagerServer::Append(const Options& options,
                             const string& key,
                             const string& new_value) {
  CHECK(options.type != ServerDB::UNKNOWN);
  CHECK(options.type != ServerDB::TOP_DIR_PLACEHOLDER);
  if (options.type > ServerDB::TOP_DIR_PLACEHOLDER) {
    CHECK(!options.name.empty());
  }
  return DBManager::Append(options, key, new_value);
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

  string key = GenKey(options);
  LOG(INFO) << "Generated mutex for " << key;

  CHECK(!ContainsKey(db_mutex_, key)) << "Already have a mutex for " << key;

  db_mutex_[key] = new mutex();

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

UserID DBManagerServer::GetNextUserID() {
  return "USER" + CreateGUIDString();
}

DeviceID DBManagerServer::GetNextDeviceID() {
  return "DEVICE" + CreateGUIDString();
}

TopDirID DBManagerServer::GetNextTopDirID() {
  return "TOPDIR" + CreateGUIDString();
}

mutex* DBManagerServer::get_mutex(const Options& options) {
  string key(GenKey(options));
  auto ret_mutex = db_mutex_.find(key);
  CHECK(ret_mutex != db_mutex_.end()) << "Couldn't find mutex for " << key;
  return ret_mutex->second;
}

UserID DBManagerServer::EmailToUserID(const string& email) {
  string user_id;
  Get(DBManager::Options(ServerDB::EMAIL_USER, ""), email, &user_id);
  return user_id;
}

bool DBManagerServer::AddEmailToTopDir(const string& email,
                                       const TopDirID& top_dir) {
  UserID user(EmailToUserID(email));
  if (user.empty()) {
    LOG(INFO) << "Could not find email " << email;
    return false;
  }
  Append(DBManager::Options(ServerDB::USER_TOP_DIR, ""),
         user, top_dir);
  Put(DBManager::Options(ServerDB::TOP_DIR_META, top_dir),
      "EDITORS_" + user, user);
  return true;
}

} // namespace lockbox
