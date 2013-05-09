#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/file_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_number_conversions.h"
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
  UserID user_id =
      Exec<UserID, const UserAuth&>(
          &LockboxServiceClient::RegisterUser, *user_auth_);
  DeviceID device_id =
      Exec<DeviceID, const UserAuth&>(
          &LockboxServiceClient::RegisterDevice, *user_auth_);
  TopDirID top_dir_id =
      Exec<TopDirID, const UserAuth&>(
          &LockboxServiceClient::RegisterTopDir, *user_auth_);

  DBManagerClient::Options dir_loc_options;
  dir_loc_options.type = ClientDB::TOP_DIR_LOCATION;
  dbm_->Put(dir_loc_options, base::Int64ToString(top_dir_id),
            FLAGS_register_top_dir);
}

void Client::Start() {
  // Prepare to start the various watchers.
  map<int64, lockbox::FileWatcherThread*> top_dir_watchers;
  map<int64, lockbox::FileEventQueueHandler*> top_dir_queues;

  Encryptor encryptor(dbm_);

  // For all of the top_dirs that are associated with this account, we need to
  // start up various facilities.
  DBManagerClient::Options options;
  options.type = lockbox::ClientDB::TOP_DIR_LOCATION;
  options.name.clear();
  leveldb::DB* db = dbm_->db(options);
  scoped_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    // Get the TOP DIR id.
    int64 top_dir_id = 0;
    CHECK(base::StringToInt64(it->key().ToString(), &top_dir_id))
        << it->key().ToString();

    // Make sure that we have the top dir databases watched.
    lockbox::DBManagerClient::Options options;
    options.type = lockbox::ClientDB::TOP_DIR_PLACEHOLDER;
    options.name = it->key().ToString();
    dbm_->NewTopDir(options);

    options.type = ClientDB::RELPATH_LOCK;
    dbm_->Clean(options);

    // Per top directory init and start.
    lockbox::FileWatcherThread* file_watcher =
        new lockbox::FileWatcherThread(dbm_);
    file_watcher->Start();
    file_watcher->AddDirectory(it->value().ToString(), true /* recursive */);
    LOG(INFO) << "Starting watcher for " << top_dir_id << " --> "
              << it->value().ToString();
    top_dir_watchers[top_dir_id] = file_watcher;

    lockbox::FileEventQueueHandler* event_queue =
        new lockbox::FileEventQueueHandler(it->key().ToString(),
                                           dbm_, this, &encryptor,
                                           user_auth_);
    top_dir_queues[top_dir_id] = event_queue;
  }

  // With DBs started, we can start interacting with the updates/server.
  UpdateFromServer update_from_server(1, user_auth_, this, dbm_);

  // Use the top dir locations to seed the watcher.

  // Set the event processor running.
  lockbox::QueueFilter queue_filter(dbm_);

  LOG(INFO) << "Running as daemon.";
  while (true) {
    sleep(1);
  }
}

void Client::Share() {
}

void Client::RegisterTopDir() {
}

} // namespace lockbox
