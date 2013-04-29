#pragma once

#include <boost/thread.hpp>

namespace lockbox {
class Counter {
 public:
  Counter() : count_(0) {}

  ~Counter() {}

  void Increment();

  int Get();

 private:
  int count_;
  boost::shared_mutex mutex_;
};

} // namespace lockbox
