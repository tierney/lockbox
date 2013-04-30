#include <string>
#include <vector>

#include "LockboxService.h"
#include "base/basictypes.h"
#include "base/file_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "client.h"
#include "crypto/rsa_private_key.h"
#include "db_manager_client.h"
#include "file_event_queue_handler.h"
#include "file_util.h"
#include "file_watcher_thread.h"
#include "leveldb/db.h"
#include "lockbox_types.h"
#include "queue_filter.h"

#include "rsa_public_key_openssl.h"
#include "rsa.h"

#include "crypto/openssl_util.h"
#include <openssl/bio.h>
#include <openssl/x509.h>

using std::string;
using std::vector;

namespace lockbox {


} // namespace lockbox

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check usage in code." << std::endl;
    return 1;
  }

  lockbox::Client::ConnInfo conn_info(argv[1], atoi(argv[2]));
  lockbox::Client client(conn_info);

  string home_dir(lockbox::GetHomeDirectory());
  lockbox::DBManagerClient client_db(home_dir.append("/.lockbox"));

  lockbox::UserAuth user_auth;
  user_auth.email = "me2@you.com";
  user_auth.password = "password";

  // See if the databases are already full of interesting data.
  lockbox::DBManagerClient::Options options;
  options.type = lockbox::ClientDB::CLIENT_DATA;
  string value;

  // Initialize the private key if necessary.
  client_db.Get(options, "PRIV_KEY", &value);
  if (value.empty()) {
    // Generate the key.
    lockbox::RSAPEM rsa_pem;

    string priv_key;
    string pub_key;

    rsa_pem.Generate(user_auth.password, &priv_key, &pub_key);

    client_db.Put(options, "PRIV_KEY", priv_key);
    LOG(INFO) << "PRIV_KEY " << priv_key;

    // // Set the public key in the EMAIL_KEY db.
    // vector<uint8> export_pub;
    options.type = lockbox::ClientDB::EMAIL_KEY;
    client_db.Put(options, user_auth.email, pub_key);

    // Update the public key in the cloud.
    lockbox::PublicKey pub_key_send;
    pub_key_send.key.clear();
    pub_key_send.key = pub_key;
    bool ret = client.Exec<bool,
                           const lockbox::UserAuth&, const lockbox::PublicKey&>(
        &lockbox::LockboxServiceClient::AssociateKey,
        user_auth, pub_key_send);
    CHECK(ret);

    // FORCE FIRST TIME STARTUP WITH THIS.

    lockbox::UserID user_id =
        client.Exec<lockbox::UserID, const lockbox::UserAuth&>(
            &lockbox::LockboxServiceClient::RegisterUser,
            user_auth);
    lockbox::DeviceID device_id =
        client.Exec<lockbox::DeviceID, const lockbox::UserAuth&>(
            &lockbox::LockboxServiceClient::RegisterDevice,
            user_auth);
    lockbox::TopDirID top_dir_id =
        client.Exec<lockbox::TopDirID, const lockbox::UserAuth&>(
            &lockbox::LockboxServiceClient::RegisterTopDir,
            user_auth);

    lockbox::DBManagerClient::Options dir_loc_options;
    dir_loc_options.type = lockbox::ClientDB::TOP_DIR_LOCATION;
    client_db.Put(dir_loc_options, base::Int64ToString(top_dir_id),
                  "/home/tierney/Lockbox");
  }

  // Prepare to start the various watchers.
  map<int64, lockbox::FileWatcherThread*> top_dir_watchers;
  map<int64, lockbox::FileEventQueueHandler*> top_dir_queues;

  lockbox::Encryptor encryptor(&client_db);

  options.type = lockbox::ClientDB::TOP_DIR_LOCATION;
  options.name.clear();
  leveldb::DB* db = client_db.db(options);
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
    client_db.NewTopDir(options);

    // Per top directory init and start.
    lockbox::FileWatcherThread* file_watcher =
        new lockbox::FileWatcherThread(&client_db);
    file_watcher->Start();
    file_watcher->AddDirectory(it->value().ToString(), true /* recursive */);
    LOG(INFO) << "Starting watcher for " << top_dir_id << " --> "
              << it->value().ToString();
    top_dir_watchers[top_dir_id] = file_watcher;

    lockbox::FileEventQueueHandler* event_queue =
        new lockbox::FileEventQueueHandler(it->key().ToString(),
                                           &client_db, &client, &encryptor,
                                           &user_auth);
    top_dir_queues[top_dir_id] = event_queue;
  }

  // Use the top dir locations to seed the watcher.

  // Set the event processor running.
  lockbox::QueueFilter queue_filter(&client_db);







  // lockbox::UserID user_id =
  //     client.Exec<lockbox::UserID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterUser,
  //         user_auth);
  // lockbox::DeviceID device_id =
  //     client.Exec<lockbox::DeviceID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterDevice,
  //         user_auth);
  // lockbox::TopDirID top_dir_id =
  //     client.Exec<lockbox::TopDirID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterTopDir,
  //         user_auth);

  // std::cout << "UID " << user_id << std::endl;
  // std::cout << "DeviceID " << device_id << std::endl;
  // std::cout << "TopDirID " << top_dir_id << std::endl;

  while (true) {
    sleep(1);
  }
  return 0;
}
