#pragma once

#include <mutex>

using std::mutex;

// Standard helper class to tie mutex lock/unlock to a scope. Blocking
// instantiation.
class ScopedMutexLock {
 public:
  explicit ScopedMutexLock(mutex* m)
    : mutex_(m) {
    mutex_->lock();
  }

  ~ScopedMutexLock() {
    mutex_->unlock();
  }

 private:
  mutex* mutex_;
};
