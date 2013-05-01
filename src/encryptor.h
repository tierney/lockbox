#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

namespace lockbox {

class Encryptor {
 public:

  static bool Encrypt(const string& path, const vector<string>& users,
                      string* data, map<string, string>* user_enc_session);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Encryptor);
};

} // namespace lockbox
