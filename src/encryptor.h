#pragma once

#include <map>
#include <string>
#include <vector>

#include "base/logging.h"
#include "gflags/gflags.h"
#include "db_manager_client.h"

using std::map;
using std::string;
using std::vector;

namespace lockbox {

class Encryptor {
 public:

  explicit Encryptor(DBManagerClient* dbm);

  virtual ~Encryptor();

  bool Encrypt(const string& path, const vector<string>& users,
               string* data, map<string, string>* user_enc_session);

  bool Decrypt(const string& data,
               const map<string, string>& user_enc_session,
               string* out_path);

 private:
  DBManagerClient* dbm_;

  DISALLOW_COPY_AND_ASSIGN(Encryptor);
};

} // namespace lockbox
