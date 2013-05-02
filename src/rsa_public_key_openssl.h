#pragma once

#include <string>
#include <vector>
#include <openssl/rsa.h>

#include "base/basictypes.h"

using std::string;
using std::vector;

namespace lockbox {

class RSAPublicKey {
 public:

  static RSA* PublicKeyToRSA(const vector<uint8>& pub);
  static RSA* PublicKeyToRSA(const string& pub);

 private:

};

} // namespace lockbox
