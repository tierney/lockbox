#pragma once

#include "base/basictypes.h"
#include <boost/thread.hpp>

namespace lockbox {
class Counter {
 public:
  Counter() : count_(0) {}

  ~Counter() {}

  int64_t Increment();

  int64_t Get();

  void Set(uint64_t val);

 private:
  uint64_t count_;
  boost::shared_mutex mutex_;
};

} // namespace lockbox
