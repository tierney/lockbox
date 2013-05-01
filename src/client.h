// Templated client that does what we want.
//
// lockbox::UserID user_id =
//     client.Exec<lockbox::UserID, const lockbox::UserAuth&>(
//         &lockbox::LockboxServiceClient::RegisterUser,
//         auth);
// lockbox::DeviceID device_id =
//     client.Exec<lockbox::DeviceID, const lockbox::UserAuth&>(
//         &lockbox::LockboxServiceClient::RegisterDevice,
//         auth);
// lockbox::TopDirID top_dir_id =
//     client.Exec<lockbox::TopDirID, const lockbox::UserAuth&>(
//         &lockbox::LockboxServiceClient::RegisterTopDir,
//         auth);
#pragma once

#include "LockboxService.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

namespace lockbox {

class Client {
 public:
  struct ConnInfo {
    ConnInfo(std::string host, int port) : host(host), port(port) {}

    std::string host;
    int port;
  };

  Client(const ConnInfo& conn_info)
    : socket_(new apache::thrift::transport::TSocket(conn_info.host,
                                                       conn_info.port)),
      transport_(new apache::thrift::transport::TFramedTransport(socket_)),
      protocol_(new apache::thrift::protocol::TBinaryProtocol(transport_)),
      client_(protocol_),
      host_(conn_info.host),
      port_(conn_info.port) {
  }

  virtual ~Client() {}

  template<typename R, typename... Args>
  R Exec(R(LockboxServiceClient::*func)(Args...), Args... args) {
    transport_->open();
    R ret = (client_.*func)(std::forward<Args>(args)...);
    transport_->close();
    return ret;
  }

 private:
  boost::shared_ptr<apache::thrift::transport::TSocket> socket_;
  boost::shared_ptr<apache::thrift::transport::TTransport> transport_;
  boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol_;

  LockboxServiceClient client_;

  std::string host_;
  int port_;
};

} // namespace lockbox
