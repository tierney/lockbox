#include "LockboxService.h"

#include "remote_execute.h"

namespace lockbox {

} // namespace lockbox

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check usage in code." << std::endl;
    return 1;
  }

  lockbox::ConnInfo conn_info(argv[1], atoi(argv[2]));
  lockbox::LockboxClient<lockbox::UserID, const lockbox::UserAuth&>::Type
      register_user(conn_info, &lockbox::LockboxServiceClient::RegisterUser);
  lockbox::LockboxClient<lockbox::DeviceID, const lockbox::UserAuth&>::Type
      register_device(conn_info, &lockbox::LockboxServiceClient::RegisterDevice);


  lockbox::UserAuth auth;
  auth.email = "me@you.com";
  auth.password = "password";
  register_user.Run(auth);

  return 0;
}
