#pragma once

#include <boost/thread/thread.hpp>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "db_manager_server.h"
#include "update_queue_sync.h"

using std::string;
using std::vector;
using std::mutex;
using std::condition_variable;
using std::lock_guard;
using std::unique_lock;

namespace lockbox {

// TODO(tierney): Graceful shutdown of the thread_group threads.
class UpdateQueuer {
 public:
  // Does not take ownership of |dbm|.
  UpdateQueuer(DBManagerServer* dbm, Sync* sync);

  ~UpdateQueuer();

  void Run();

  void size() const;

  void Increment();

  void Decrement();

 private:
  DBManagerServer* dbm_;

  Sync* sync_;

  vector<boost::thread*> threads_;
  boost::thread_group group_;
};


} // namespace lockbox
