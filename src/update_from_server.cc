#include "update_from_server.h"

#include <chrono>
#include <functional>

#include "LockboxService.h"
#include "lockbox_types.h"
#include "base/strings/string_split.h"

using std::bind;

namespace lockbox {

UpdateFromServer::UpdateFromServer(DeviceID device_id, UserAuth* user_auth,
                                   Client* client,
                                   DBManagerClient* dbm)
    : thread_(new thread(bind(&UpdateFromServer::Run, this))),
      device_id_(device_id),
      user_auth_(user_auth),
      client_(client),
      dbm_(dbm) {
}

UpdateFromServer::~UpdateFromServer() {
  delete thread_;
}

void UpdateFromServer::Run() {
  while (true) {
    // Format of UpdateList.updates (underscore-separated):
    // 1367949789_1_25baec40-5a1f-108b-4ca31a19-3ab710a6_yUCJ/6CWfX2Uin3kzy6cZC7L9Wc=,1367949886_1_15d0b173-399d-714f-1006a1f4-36212573_EsrNz+zxVv3Zy3eXoElaeAHZWsk=

    // Grab updates from the server.
    UpdateList updates;
    try {
      client_->Exec<void, UpdateList&, const UserAuth&, const DeviceID>(
          &LockboxServiceClient::PollForUpdates, updates,
          *user_auth_, device_id_);
    } catch (std::exception& e) {
      LOG(WARNING) << "Well polling kind of broke." << e.what();
      continue;
    }
    if (updates.updates.empty()) {
      std::chrono::milliseconds dura(1000);
      std::this_thread::sleep_for(dura);
      continue;
    }

    LOG(INFO) << "Received updates";

    // Persist the updates.
    DBManagerClient::Options options;
    options.type = ClientDB::UPDATE_QUEUE_SERVER;

    vector<string> update_list;
    base::SplitString(updates.updates, ',', &update_list);
    for (const string& update : update_list) {
      vector<string> update_params;
      base::SplitString(update, '_', &update_params);
      options.name = update_params[1];

      dbm_->Append(options, update, "");
    }

    // Delete the updates on the server.
    client_->Exec<void, const UserAuth&, const DeviceID, const UpdateList&>(
        &LockboxServiceClient::PersistedUpdates,
        *user_auth_, device_id_, updates);
  }
}

} // namespace lockbox
