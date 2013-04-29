#pragma once

#include "LockboxService.h"

namespace lockbox {

class LockboxServiceHandler : virtual public LockboxServiceIf {
 public:
  LockboxServiceHandler();

  UserID RegisterUser(const UserAuth& user);

  DeviceID RegisterDevice(const UserAuth& user);

  TopDirID RegisterTopDir(const UserAuth& user);

  bool LockRelPath(const PathLock& lock);

  int64_t UploadPackage(const LocalPackage& pkg);

  void DownloadPackage(LocalPackage& _return, const DownloadRequest& req);

  void PollForUpdates(Updates& _return,
                      const UserAuth& auth,
                      const DeviceID device);

  void Send(const UserAuth& sender,
            const std::string& receiver_email,
            const VersionInfo& vinfo);

  void GetLatestVersion(VersionInfo& _return,
                        const UserAuth& requestor,
                        const std::string& receiver_email);
};

} // namespace lockbox
