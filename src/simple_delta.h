#pragma once

#include <string>

using std::string;

namespace lockbox {

class Delta {
 public:
  static string Generate(const string& first, const string& second);

  static string Apply(const string& first, const string& delta);
};

} // namespace lockbox
