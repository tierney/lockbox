#pragma once

#include <librsync.h>
#include <string>

using std::string;

namespace lockbox {

class Rsync {
 public:
  Rsync(int blocksize);

  virtual ~Rsync();

  rs_result GenerateDelta(const string& first, const string& second,
                     string* output);

  void ApplyDelta(const string& first, const string& delta,
                  string* output);

 private:
  int blocksize_;
};

} // namespace lockbox
