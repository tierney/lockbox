#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/file_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "client.h"
#include "crypto/openssl_util.h"
#include "crypto/rsa_private_key.h"
#include "db_manager_client.h"
#include "file_event_queue_handler.h"
#include "file_util.h"
#include "file_watcher_thread.h"
#include "gflags/gflags.h"
#include "leveldb/db.h"
#include "lockbox_types.h"
#include "queue_filter.h"
#include "rsa.h"
#include "rsa_public_key_openssl.h"
#include "update_from_server.h"
#include <openssl/bio.h>
#include <openssl/x509.h>

DECLARE_string(register_top_dir);
DECLARE_string(share);

namespace lockbox {

void Client::RegisterUser() {
  // Generate the key.
  RSAPEM rsa_pem;
  string priv_key;
  string pub_key;
  rsa_pem.Generate(user_auth_->password, &priv_key, &pub_key);

  // See if the databases are already full of interesting data.
  lockbox::DBManagerClient::Options options;
  options.type = lockbox::ClientDB::CLIENT_DATA;

  // TODO(tierney): Check that a key doesn't already exist?
  dbm_->Put(options, "PRIV_KEY", priv_key);
  LOG(INFO) << "PRIV_KEY " << priv_key;

  // Set the public key in the EMAIL_KEY db.
  options.type = ClientDB::EMAIL_KEY;
  dbm_->Put(options, user_auth_->email, pub_key);

  // Update the public key in the cloud.
  PublicKey pub_key_send;
  pub_key_send.key.clear();
  pub_key_send.key = pub_key;
  bool ret = Exec<bool, const UserAuth&, const PublicKey&>(
      &LockboxServiceClient::AssociateKey,
      *user_auth_, pub_key_send);
  CHECK(ret);

  // Remote registration functions.
  UserID user_id;
  Exec<void, UserID&, const UserAuth&>(
      &LockboxServiceClient::RegisterUser, user_id, *user_auth_);
  CHECK(!user_id.empty());

  DeviceID device_id;
  Exec<void, DeviceID&, const UserAuth&>(
      &LockboxServiceClient::RegisterDevice, device_id, *user_auth_);
  CHECK(!device_id.empty());
  dbm_->Put(DBManager::Options(ClientDB::CLIENT_DATA, ""),
            "DEVICE", device_id);

  TopDirID top_dir_id;
  Exec<void, TopDirID&, const UserAuth&>(
      &LockboxServiceClient::RegisterTopDir, top_dir_id, *user_auth_);
  CHECK(!top_dir_id.empty());

  DBManagerClient::Options dir_loc_options;
  dir_loc_options.type = ClientDB::TOP_DIR_LOCATION;
  dbm_->Put(dir_loc_options, top_dir_id, FLAGS_register_top_dir);

  dbm_->Put(DBManager::Options(ClientDB::LOCATION_TOP_DIR, ""),
            FLAGS_register_top_dir, top_dir_id);
}

void Client::Start() {
  // Prepare to start the various watchers.
  map<TopDirID, lockbox::FileWatcherThread*> top_dir_watchers;
  map<TopDirID, lockbox::FileEventQueueHandler*> top_dir_queues;

  string device_id_str;
  dbm_->Get(DBManagerClient::Options(ClientDB::CLIENT_DATA, ""),
            "DEVICE", &(user_auth_->device));

  Encryptor encryptor(dbm_, user_auth_);

  // Check if there are shared directories from the cloud that we should add to
  // our set.
  // TODO(tierney): We currently require a restart to get new directories from
  // the cloud. We should be able to detect and dynamically add new ones.
  vector<TopDirID> top_dirs;
  Exec<void, vector<TopDirID>&, const UserAuth&>(
      &LockboxServiceClient::GetTopDirs, top_dirs, *user_auth_);

  LOG(INFO) << "Got TopDirs from Server";
  for (const TopDirID& top_dir : top_dirs) {
    LOG(INFO) << "  " << top_dir;
    string location;
    dbm_->Get(DBManager::Options(ClientDB::TOP_DIR_LOCATION, ""),
              top_dir, &location);
    if (!location.empty()) {
      continue;
    }

    // TODO(tierney):Get the location from the user.
    const string shared_path("/home/tierney/Lockboxes/" + top_dir);
    dbm_->Put(DBManager::Options(ClientDB::TOP_DIR_LOCATION, ""),
              top_dir, shared_path);
    CHECK(file_util::CreateDirectory(base::FilePath(shared_path)));
  }

  // For all of the top_dirs that are associated with this account, we need to
  // start up various facilities.
  DBManagerClient::Options options;
  options.type = lockbox::ClientDB::TOP_DIR_LOCATION;
  options.name.clear();
  leveldb::DB* db = dbm_->db(options);
  scoped_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    // Get the TOP DIR id.
    const TopDirID& top_dir_id = it->key().ToString();

    const string& abs_path = it->value().ToString();

    // Make sure that we have the top dir databases watched.
    lockbox::DBManagerClient::Options options;
    options.type = lockbox::ClientDB::TOP_DIR_PLACEHOLDER;
    options.name = top_dir_id;
    dbm_->NewTopDir(options);

    options.type = ClientDB::RELPATH_LOCK;
    dbm_->Clean(options);

    // Per top directory init and start.
    lockbox::FileWatcherThread* file_watcher =
        new lockbox::FileWatcherThread(dbm_);
    file_watcher->Start();
    file_watcher->AddDirectory(abs_path, true /* recursive */);
    LOG(INFO) << "Starting watcher for " << top_dir_id << " --> "
              << abs_path;
    top_dir_watchers[top_dir_id] = file_watcher;

    lockbox::FileEventQueueHandler* event_queue =
        new lockbox::FileEventQueueHandler(top_dir_id, dbm_, this, &encryptor,
                                           user_auth_);
    top_dir_queues[top_dir_id] = event_queue;
  }

  // With DBs started, we can start interacting with the updates/server.
  UpdateFromServer update_from_server(user_auth_, this, dbm_);

  // Use the top dir locations to seed the watcher.

  // Set the event processor running.
  lockbox::QueueFilter queue_filter(dbm_);

  LOG(INFO) << "Running as daemon.";
  while (true) {
    sleep(1);
  }
}

void Client::Share() {
  // Split the DIRECTORY, EMAIL.
  vector<string> dir_email;
  base::SplitString(FLAGS_share, ',', &dir_email);
  CHECK(dir_email.size() == 2);
  const string& dir = dir_email[0];
  const string& email = dir_email[1];

  // CHECK that the directory exists.
  const TopDirID top_dir_id(dbm_->TopDirPathToID(dir));
  CHECK(!top_dir_id.empty());

  // CHECK that we can grab the public key.
  PublicKey key;
  Exec<void, PublicKey&, const string&>(
      &LockboxServiceClient::GetKeyFromEmail, key, email);
  CHECK(!key.key.empty());

  // Put the key in our keyring.
  dbm_->Put(DBManager::Options(ClientDB::EMAIL_KEY, ""), email, key.key);

  // Share the directory with the user
  bool success =
      Exec<bool, const UserAuth&, const string&, const TopDirID&>(
          &LockboxServiceClient::ShareTopDir, *user_auth_, email, top_dir_id);
  CHECK(success);
}

void Client::RegisterTopDir() {
}

} // namespace lockbox
