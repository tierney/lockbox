#include <string>

#include "client.h"
#include "LockboxService.h"
#include "lockbox_types.h"
#include "file_watcher_thread.h"
#include "db_manager_client.h"
#include "base/file_util.h"

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

  lockbox::DBManagerClient client_db("/tmp");
  // See if the databases are already full of interesting data.

  // Use the top dir locations to seed the watcher.


  map<int, lockbox::FileWatcherThread*> top_dir_watchers;
  lockbox::FileWatcherThread file_watcher(&client_db);
  file_watcher.Start();
  file_watcher.AddDirectory("/home/tierney/Lockbox", true /* recursive */);


  lockbox::UserAuth auth;
  auth.email = "me2@you.com";
  auth.password = "password";

  lockbox::UserID user_id =
      client.Exec<lockbox::UserID, const lockbox::UserAuth&>(
          &lockbox::LockboxServiceClient::RegisterUser,
          auth);
  lockbox::DeviceID device_id =
      client.Exec<lockbox::DeviceID, const lockbox::UserAuth&>(
          &lockbox::LockboxServiceClient::RegisterDevice,
          auth);
  lockbox::TopDirID top_dir_id =
      client.Exec<lockbox::TopDirID, const lockbox::UserAuth&>(
          &lockbox::LockboxServiceClient::RegisterTopDir,
          auth);

  std::cout << "UID " << user_id << std::endl;
  std::cout << "DeviceID " << device_id << std::endl;
  std::cout << "TopDirID " << top_dir_id << std::endl;

  while (true) {
    sleep(1);
  }
  return 0;
}
