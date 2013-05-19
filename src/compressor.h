#pragma once

#include <string>

using std::string;

namespace lockbox {

class Gzip {
 public:

  static void Compress(const string& input, string* output);

  static void Decompress(const string& input, string* output);
};

} // namespace lockbox
