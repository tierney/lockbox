#include "hash_util.h"

#include "base/sha1.h"
#include "base/strings/string_number_conversions.h"

namespace lockbox {

string SHA1Hex(const string& input) {
  const string raw_sha1(base::SHA1HashString(input));
  return base::HexEncode(raw_sha1.c_str(), raw_sha1.length());
}

} // namespace lockbox
