#include "lockbox_service_handler.h"

#include "base/strings/string_number_conversions.h"

namespace lockbox {

LockboxServiceHandler::LockboxServiceHandler(DBManager* manager)
    : manager_(manager) {
  CHECK(manager);
}

UserID LockboxServiceHandler::RegisterUser(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterUser\n");

  DBManager::Options options(LockboxDatabase::EMAIL_USER);
  string value;
  manager_->Get(options, user.email, &value);
  if (!value.empty()) {
    LOG(INFO) << "User already registered " << user.email;
    return -1;
  }

  UserID uid = manager_->GetNextUserID();
  string uid_to_persist = base::IntToString(uid);
  manager_->Put(options, user.email, uid_to_persist);
  return uid;
}

DeviceID LockboxServiceHandler::RegisterDevice(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterDevice\n");
  DBManager::Options options(LockboxDatabase::USER_DEVICE);
  string value;
  DeviceID device_id = manager_->GetNextDeviceID();
  string device_id_to_persist = base::IntToString(device_id);

  // TODO(tierney): In the future, we can defensively check against an IP
  // address for an email account to throttle the accounts.
  manager_->Update(options, user.email, device_id_to_persist);
  return device_id;
}

TopDirID LockboxServiceHandler::RegisterTopDir(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterTopDir\n");
  DBManager::Options options(LockboxDatabase::USER_TOP_DIR);
  string value;
  TopDirID top_dir_id = manager_->GetNextTopDirID();
  string top_dir_id_to_persist = base::IntToString(top_dir_id);

  CHECK(manager_->Update(options, user.email, top_dir_id_to_persist));

  // TODO(tierney): Should create additional top_dir database here.
  options.type = LockboxDatabase::TOP_DIR_PLACEHOLDER;
  options.name = top_dir_id_to_persist;
  CHECK(manager_->NewTopDir(options));
  return top_dir_id;
}

bool LockboxServiceHandler::AcquireLockRelPath(const PathLock& lock) {
  // Your implementation goes here
  printf("LockRelPath\n");
}

void LockboxServiceHandler::ReleaseLockRelPath(const PathLock& lock) {

}

int64_t LockboxServiceHandler::UploadPackage(const LocalPackage& pkg) {
  // Your implementation goes here
  printf("UploadPackage\n");
}

void LockboxServiceHandler::DownloadPackage(LocalPackage& _return, const DownloadRequest& req) {
  // Your implementation goes here
  printf("DownloadPackage\n");
}

void LockboxServiceHandler::PollForUpdates(Updates& _return, const UserAuth& auth, const DeviceID device) {
  // Your implementation goes here
  printf("PollForUpdates\n");
}

void LockboxServiceHandler::Send(const UserAuth& sender, const std::string& receiver_email, const VersionInfo& vinfo) {
  // Your implementation goes here
  printf("Send\n");
}

void LockboxServiceHandler::GetLatestVersion(VersionInfo& _return, const UserAuth& requestor, const std::string& receiver_email) {
  // Your implementation goes here
  printf("GetLatestVersion\n");
}

} // namespace lockbox
