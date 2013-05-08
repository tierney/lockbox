#pragma once

#include <thread>

#include "client.h"
#include "db_manager_client.h"

using std::thread;

namespace lockbox {

class UpdateFromServer {
 public:
  // Does not take ownership of |client|.
  explicit UpdateFromServer(DeviceID device_id, UserAuth* user_auth,
                            Client* client, DBManagerClient* dbm);

  virtual ~UpdateFromServer();

  void Run();

 private:
  thread* thread_;

  DeviceID device_id_;
  UserAuth* user_auth_;
  Client* client_;
  DBManagerClient* dbm_;
};

} // namespace lockbox
