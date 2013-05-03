#include "util.h"

#include <algorithm>

namespace lockbox {

bool IsPrefixOf(const string& first, const string& second) {
  auto res = std::mismatch(first.begin(), first.end(), second.begin());
  return (res.first == first.end());
}

string RemoveBaseFromInput(const string& base, const string& input) {
  string ret(input);
  ret.erase(0, base.length());
  return ret;
}

} // namespace lockbox
