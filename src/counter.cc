#include "counter.h"

namespace lockbox {

void Counter::Increment() {
  boost::upgrade_lock<boost::shared_mutex> lock(mutex_);
  boost::upgrade_to_unique_lock<boost::shared_mutex> unique_lock(lock);
  ++count_;
}

int Counter::Get() {
  boost::shared_lock<boost::shared_mutex> lock(mutex_);
  return count_;
}

} // namespace lockbox
