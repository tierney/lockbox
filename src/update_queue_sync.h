#pragma once

#include <mutex>
#include <condition_variable>

using std::mutex;
using std::condition_variable;

namespace lockbox {

struct Sync {
  mutex cv_mutex;
  condition_variable cv;
  mutex db_mutex;
};

} // namespace lockbox
