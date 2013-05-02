#include "lockbox_service_handler.h"

#include "base/strings/string_number_conversions.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>

namespace lockbox {

LockboxServiceHandler::LockboxServiceHandler(DBManagerServer* manager)
    : manager_(manager) {
  CHECK(manager);
}

UserID LockboxServiceHandler::RegisterUser(const UserAuth& user) {
  // Your implementation goes here
  printf("RegisterUser\n");

  DBManagerServer::Options options;
  options.type = static_cast<int>(ServerDB::EMAIL_USER);
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
  DBManagerServer::Options options;
  options.type = ServerDB::USER_DEVICE;

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
  DBManagerServer::Options options;
  options.type = ServerDB::USER_TOP_DIR;

  string value;
  TopDirID top_dir_id = manager_->GetNextTopDirID();
  string top_dir_id_to_persist = base::IntToString(top_dir_id);

  CHECK(manager_->Update(options, user.email, top_dir_id_to_persist));

  // TODO(tierney): Should create additional top_dir database here.
  options.type = ServerDB::TOP_DIR_PLACEHOLDER;
  options.name = top_dir_id_to_persist;
  CHECK(manager_->NewTopDir(options));
  return top_dir_id;
}

void LockboxServiceHandler::AcquireLockRelPath(PathLockResponse& _return,
                                               const PathLockRequest& lock) {
  // Your implementation goes here
  printf("LockRelPath\n");

  // TODO(tierney): Authenticate.

  // See if the lock is already held.

  // Set the lock.
  _return.acquired = true;

  // Get the names of the individuals with whom to share the directory.
  _return.users.push_back("me2@you.com");

  // Send the data back in the response.
  return;
}

void LockboxServiceHandler::ReleaseLockRelPath(const PathLockRequest& lock) {

}

int64_t LockboxServiceHandler::UploadPackage(const RemotePackage& pkg) {
  // Your implementation goes here
  printf("UploadPackage\n");
  int64_t ret = pkg.payload.data.size();

  LOG(INFO) << "Received data (" << pkg.payload.data.size() << ") :"
            << pkg.payload.data;

  for (auto& ptr : pkg.payload.user_enc_session) {
    LOG(INFO) << "  " << ptr.first << " : " << ptr.second;
  }

  boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> mem_buf(
      new apache::thrift::transport::TMemoryBuffer());
  boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> bin_prot(
      new apache::thrift::protocol::TBinaryProtocol(mem_buf));

  pkg.write(bin_prot.get());
  string mem = mem_buf->getBufferAsString();
  LOG(INFO) << "Did it work?: " << mem.size();
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
