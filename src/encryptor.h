#pragma once

#include <map>
#include <string>
#include <vector>

#include "base/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::string;
using std::vector;

namespace lockbox {

class Encryptor {
 public:

  // explicit Encryptor();

  // virtual ~Encryptor();

  static bool Encrypt(const string& path, const vector<string>& users,
                      string* data, map<string, string>* user_enc_session);

  static bool Decrypt(const string& data,
                      const map<string, string>& user_enc_session,
                      const string& out_path);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Encryptor);
};

} // namespace lockbox
