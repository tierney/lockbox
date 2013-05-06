#pragma once

#include <mutex>
#include <condition_variable>

using std::mutex;
using std::condition_variable;

namespace lockbox {

struct Sync {
  mutex m;
  condition_variable cv;
};

} // namespace lockbox
