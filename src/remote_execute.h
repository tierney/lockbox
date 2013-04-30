// Templated class that created too much redundancy after all.
// namespace lockbox {
//
// class Client {
//  public:
//   explicit Client(const ConnInfo& conn_info) :
//       conn_info_(conn_info),
//       register_user_(conn_info, &LockboxServiceClient::RegisterUser),
//       register_device_(conn_info, &LockboxServiceClient::RegisterDevice),
//       register_top_dir_(conn_info, &LockboxServiceClient::RegisterTopDir),
//       lock_rel_path_(conn_info, &LockboxServiceClient::LockRelPath),
//       upload_package_(conn_info, &LockboxServiceClient::UploadPackage),
//       download_package_(conn_info, &LockboxServiceClient::DownloadPackage),
//       poll_for_updates_(conn_info, &LockboxServiceClient::PollForUpdates),
//       send_(conn_info, &LockboxServiceClient::Send),
//       get_latest_version_(conn_info, &LockboxServiceClient::GetLatestVersion) {
//   }
//
//   virtual ~Client() {
//   }
//
//   UserID RegisterUser(const UserAuth& auth) {
//     return register_user_.Run(auth);
//   }
//
//   DeviceID RegisterDevice(const UserAuth& auth) {
//     return register_device_.Run(auth);
//   }
//
//   TopDirID RegisterTopDir(const UserAuth& auth) {
//     return register_top_dir_.Run(auth);
//   }
//
//  private:
//   ConnInfo conn_info_;
//   LockboxClient<UserID, const UserAuth&>::Type register_user_;
//   LockboxClient<DeviceID, const UserAuth&>::Type register_device_;
//   LockboxClient<TopDirID, const UserAuth&>::Type register_top_dir_;
//   LockboxClient<bool, const PathLock&>::Type lock_rel_path_;
//   LockboxClient<int64_t, const LocalPackage&>::Type upload_package_;
//   LockboxClient<void, LocalPackage&, const DownloadRequest&>::Type download_package_;
//   LockboxClient<void, Updates&, const UserAuth&, const DeviceID>::Type poll_for_updates_;
//   LockboxClient<void, const UserAuth&, const string&, const VersionInfo&>::Type send_;
//   LockboxClient<void, VersionInfo&, const UserAuth&, const string&>::Type get_latest_version_;
// };
//
// } // namespace lockbox

#include <string>
#include <utility>
#include <functional>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "LockboxService.h"

namespace lockbox {

struct ConnInfo {
  ConnInfo(std::string host, int port) : host(host), port(port) {}

  std::string host;
  int port;
};

// Generic thrift-based remote execution templated class.
template<typename T, typename R, typename... Args>
class RemoteExecute {
 public:
  RemoteExecute(const ConnInfo& conn_info, R(T::*func)(Args...))
      : socket_(new apache::thrift::transport::TSocket(conn_info.host,
                                                       conn_info.port)),
        transport_(new apache::thrift::transport::TFramedTransport(socket_)),
        protocol_(new apache::thrift::protocol::TBinaryProtocol(transport_)),
        client_(protocol_),
        func_(func),
        host_(conn_info.host),
        port_(conn_info.port) {}

  virtual ~RemoteExecute() {}

  R Run(Args &&... args) {
    transport_->open();
    R ret = (client_.*func_)(std::forward<Args>(args)...);
    transport_->close();
    return ret;
  }

 private:
  boost::shared_ptr<apache::thrift::transport::TSocket> socket_;
  boost::shared_ptr<apache::thrift::transport::TTransport> transport_;
  boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol_;

  T client_;

  R(T::*func_)(Args...);

  std::string host_;
  int port_;
};

// Lockbox-specific type for the RemoteExecute class.
template<typename R, typename... Args>
struct LockboxClient {
  typedef RemoteExecute<lockbox::LockboxServiceClient, R, Args...> Type;
};

} // namespace lockbox
