#pragma once

#if defined(OS_MACOSX)
#define BOOST_NO_CXX11_NUMERIC_LIMITS 1
#endif
#include <boost/thread.hpp>

#include "base/basictypes.h"


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
