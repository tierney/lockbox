#include <string>

#include "client.h"
#include "LockboxService.h"
#include "lockbox_types.h"
#include "file_watcher_thread.h"
#include "db_manager_client.h"
#include "base/file_util.h"
#include "file_util.h"
#include "leveldb/db.h"
#include "base/strings/string_number_conversions.h"
#include "queue_filter.h"

using std::string;

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

  // See if the databases are already full of interesting data.
  lockbox::DBManagerClient::Options options;
  options.type = lockbox::ClientDB::CLIENT_DATA;
  string value;

  map<int64, lockbox::FileWatcherThread*> top_dir_watchers;
  options.type = lockbox::ClientDB::TOP_DIR_LOCATION;
  options.name.clear();

  leveldb::DB* db = client_db.db(options);
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    int64 top_dir_id = 0;
    CHECK(base::StringToInt64(it->key().ToString(), &top_dir_id))
        << it->key().ToString();

    lockbox::DBManagerClient::Options options;
    options.type = lockbox::ClientDB::TOP_DIR_PLACEHOLDER;
    options.name = it->key().ToString();
    client_db.NewTopDir(options);

    lockbox::FileWatcherThread* file_watcher =
        new lockbox::FileWatcherThread(&client_db);
    file_watcher->Start();
    file_watcher->AddDirectory(it->value().ToString(), true /* recursive */);
    LOG(INFO) << "Starting watcher for " << top_dir_id << " --> "
              << it->value().ToString();
    top_dir_watchers[top_dir_id] = file_watcher;
  }
  delete it;

  // Use the top dir locations to seed the watcher.

  // Set the event processor running.
  lockbox::QueueFilter queue_filter(&client_db);


  lockbox::UserAuth auth;
  auth.email = "me2@you.com";
  auth.password = "password";

  // lockbox::UserID user_id =
  //     client.Exec<lockbox::UserID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterUser,
  //         auth);
  // lockbox::DeviceID device_id =
  //     client.Exec<lockbox::DeviceID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterDevice,
  //         auth);
  // lockbox::TopDirID top_dir_id =
  //     client.Exec<lockbox::TopDirID, const lockbox::UserAuth&>(
  //         &lockbox::LockboxServiceClient::RegisterTopDir,
  //         auth);

  // std::cout << "UID " << user_id << std::endl;
  // std::cout << "DeviceID " << device_id << std::endl;
  // std::cout << "TopDirID " << top_dir_id << std::endl;

  while (true) {
    sleep(1);
  }
  return 0;
}
