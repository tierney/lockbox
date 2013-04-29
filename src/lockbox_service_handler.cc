#include "lockbox_service_handler.h"

namespace lockbox {

LockboxServiceHandler::LockboxServiceHandler() {
  // Your initialization goes here
}

UserID LockboxServiceHandler::RegisterUser(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterUser\n");

  //
}

DeviceID LockboxServiceHandler::RegisterDevice(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterDevice\n");
}

TopDirID LockboxServiceHandler::RegisterTopDir(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterTopDir\n");
}

bool LockboxServiceHandler::LockRelPath(const PathLock& lock) {
  // Your implementation goes here
  printf("LockRelPath\n");
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
