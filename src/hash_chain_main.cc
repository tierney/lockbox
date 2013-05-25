#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include "base/memory/scoped_ptr.h"
#include "base/sha1.h"
#include "crypto/random.h"

const int kAverageFileSizeBytes = (1 << 20); // Bytes

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp () {
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

static inline double timestamp_delta_sec(const timestamp_t first,
                                         const timestamp_t second) {
  return (second - first) / 1000000.0L;
}

int main() {

  scoped_array<char> array(new char[kAverageFileSizeBytes]);
  crypto::RandBytes(array.get(), kAverageFileSizeBytes);

  timestamp_t first = get_timestamp();
  sleep(1);
  timestamp_t second = get_timestamp();

  std::cout << timestamp_delta_sec(first, second) << " seconds" << std::endl;
  return 0;
}
