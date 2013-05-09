#pragma once

#include <mutex>

using std::mutex;
using std::unique_lock;

namespace lockbox {

// Standard helper class to tie mutex lock/unlock to a scope. Blocking
// instantiation.
class ScopedMutexLock {
 public:
  explicit ScopedMutexLock(mutex* m)
      : mutex_(m), lock_(*m) {
  }

  ~ScopedMutexLock() {
    lock_.unlock();
  }

 private:
  mutex* mutex_;
  unique_lock<mutex> lock_;
};

} // namespace lockbox
