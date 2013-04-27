#include "LockboxService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TNonblockingServer.h>

#include <boost/thread.hpp>
#include <ctime>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using apache::thrift::concurrency::ThreadManager;
using apache::thrift::concurrency::PosixThreadFactory;
using boost::shared_ptr;

namespace lockbox {

class Counter {
 public:
  Counter() : count_(0) {}

  ~Counter() {}

  void inc() {
    boost::upgrade_lock<boost::shared_mutex> lock(mutex_);
    boost::upgrade_to_unique_lock<boost::shared_mutex> unique_lock(lock);
    ++count_;
  }

  int get() {
    boost::shared_lock<boost::shared_mutex> lock(mutex_);
    return count_;
  }

 private:
  int count_;
  boost::shared_mutex mutex_;
};

class LockboxServiceHandler : virtual public LockboxServiceIf {
 public:
  LockboxServiceHandler() {
    // Your initialization goes here
  }

  UserID RegisterUser(const UserAuth& user) {
    // Your implementation goes here
    printf("RegisterUser\n");
  }

  DeviceID RegisterDevice(const UserAuth& user) {
    // Your implementation goes here
    printf("RegisterDevice\n");
  }

  TopDirID RegisterTopDir(const UserAuth& user) {
    // Your implementation goes here
    printf("RegisterTopDir\n");
  }

  bool LockRelPath(const PathLock& lock) {
    // Your implementation goes here
    printf("LockRelPath\n");
  }

  int64_t UploadPackage(const LocalPackage& pkg) {
    // Your implementation goes here
    printf("UploadPackage\n");
  }

  void DownloadPackage(LocalPackage& _return, const DownloadRequest& req) {
    // Your implementation goes here
    printf("DownloadPackage\n");
  }

  void PollForUpdates(Updates& _return, const UserAuth& auth, const DeviceID device) {
    // Your implementation goes here
    printf("PollForUpdates\n");
  }

  void Send(const UserAuth& sender, const std::string& receiver_email, const VersionInfo& vinfo) {
    // Your implementation goes here
    printf("Send\n");
  }

  void GetLatestVersion(VersionInfo& _return, const UserAuth& requestor, const std::string& receiver_email) {
    // Your implementation goes here
    printf("GetLatestVersion\n");
  }

};

} // namespace lockbox

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Please check code for usage." << std::endl;
    return 1;
  }

  lockbox::Counter counter;

  const int port = atoi(argv[1]);
  const int num_threads = atoi(argv[2]);

  shared_ptr<lockbox::LockboxServiceHandler> handler(
      new lockbox::LockboxServiceHandler(// &counter
                                         ));
  shared_ptr<TProcessor> processor(new lockbox::LockboxServiceProcessor(handler));
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
