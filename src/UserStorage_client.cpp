#include "UserStorage.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check usage in code." << std::endl;
    return 1;
  }

  boost::shared_ptr<TSocket> socket(new TSocket(argv[1], atoi(argv[2])));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  lockbox::UserProfile profile;
  lockbox::UserStorageClient client(protocol);
  for (int i = 0; i < 100000; i++) {
    transport->open();
    client.store(profile);
    transport->close();
  }

  return 0;
}
