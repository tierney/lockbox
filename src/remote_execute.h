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
