#include "LockboxService.h"

#include "lockbox_service_handler.h"

#include <ctime>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TNonblockingServer.h>
#include "counter.h"
#include "db_manager_server.h"

#include "crypto/random.h"
#include "guid_creator.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using apache::thrift::concurrency::ThreadManager;
using apache::thrift::concurrency::PosixThreadFactory;
using boost::shared_ptr;

namespace lockbox {

} // namespace lockbox

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check code for usage." << std::endl;
    return 1;
  }

  lockbox::Counter counter;

  const int port = atoi(argv[1]);
  const int num_threads = atoi(argv[2]);

  lockbox::DBManager manager("/tmp");

  shared_ptr<lockbox::LockboxServiceHandler> handler(
      new lockbox::LockboxServiceHandler(&manager
                                         ));
  shared_ptr<TProcessor> processor(
      new lockbox::LockboxServiceProcessor(handler));
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  // Setup for the server that instantiates |num_threads| to handle requests.
  shared_ptr<ThreadManager> threadManager =
      ThreadManager::newSimpleThreadManager(num_threads);

  shared_ptr<PosixThreadFactory> threadFactory =
      shared_ptr<PosixThreadFactory>(new PosixThreadFactory());

  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TNonblockingServer server(processor, protocolFactory, port, threadManager);
  server.serve();
  return 0;
}
