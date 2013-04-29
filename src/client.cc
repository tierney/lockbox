#include "LockboxService.h"

#include "remote_execute.h"

namespace lockbox {

class Client {
 public:
  explicit Client(const ConnInfo& conn_info) :
      conn_info_(conn_info),
      register_user_(conn_info, &LockboxServiceClient::RegisterUser),
      register_device_(conn_info, &LockboxServiceClient::RegisterDevice) {
 }

  virtual ~Client() {
  }

  UserID RegisterUser(const UserAuth& auth) {
    return register_user_.Run(auth);
  }

  DeviceID RegisterDevice(const UserAuth& auth) {
    return register_device_.Run(auth);
  }

 private:
  ConnInfo conn_info_;
  LockboxClient<UserID, const UserAuth&>::Type register_user_;
  LockboxClient<DeviceID, const UserAuth&>::Type register_device_;
};

} // namespace lockbox

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check usage in code." << std::endl;
    return 1;
  }

  lockbox::ConnInfo conn_info(argv[1], atoi(argv[2]));
  lockbox::Client client(conn_info);

  lockbox::UserAuth auth;
  auth.email = "me@you.com";
  auth.password = "password";
  std::cout << "UID " << client.RegisterUser(auth) << std::endl;



  return 0;
}
