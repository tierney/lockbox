#pragma once

#include <string>

#include "LockboxService.h"
#include "counter.h"
#include "db_manager_server.h"
#include "update_queue_sync.h"

using std::string;

namespace lockbox {

class LockboxServiceHandler : virtual public LockboxServiceIf {
 public:
  // Does not take ownershi of |manager|.
  LockboxServiceHandler(DBManagerServer* manager, Sync* sync);

  void RegisterUser(UserID& _return, const UserAuth& user);

  void RegisterDevice(DeviceID& _return, const UserAuth& user);

  void RegisterTopDir(TopDirID& _return, const UserAuth& user);

  bool ShareTopDir(const UserAuth& user, const string& email,
                   const TopDirID& top_dir_id);

  void GetTopDirs(vector<TopDirID>& _return, const UserAuth& user);

  void RegisterRelativePath(string& _return,
                            const RegisterRelativePathRequest& req);

  bool AssociateKey(const UserAuth& user, const PublicKey& pub);

  void GetKeyFromEmail(PublicKey& _return, const string& email);

  void AcquireLockRelPath(PathLockResponse& _return,
                          const PathLockRequest& lock);

  void ReleaseLockRelPath(const PathLockRequest& lock);

  int64_t UploadPackage(const UserAuth& user, const RemotePackage& pkg);

  void DownloadPackage(RemotePackage& _return, const DownloadRequest& req);

  void PollForUpdates(UpdateMap& _return,
                      const UserAuth& auth,
                      const DeviceID& device);

  void GetFptrs(vector<string>& _return, const UserAuth& auth,
                const string& top_dir, const string& hash);

  void PersistedUpdates(const UserAuth& auth, const DeviceID& device,
                        const UpdateList& updates);

  void Send(const UserAuth& sender,
            const std::string& receiver_email,
            const VersionInfo& vinfo);

  void GetLatestVersion(VersionInfo& _return,
                        const UserAuth& requestor,
                        const std::string& receiver_email);
 private:
  DBManagerServer* manager_;
  Sync* sync_;
};

} // namespace lockbox
