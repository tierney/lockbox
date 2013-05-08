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

  bool Encrypt(const string& top_dir_path, const string& path,
               const vector<string>& users,
               RemotePackage* package);

  bool EncryptString(const string& top_dir_path,
                     const string& path,
                     const string& raw_input,
                     const vector<string>& users,
                     RemotePackage* package);

  bool Decrypt(const string& data,
               const map<string, string>& user_enc_session,
               string* output);

 private:
  bool EncryptInternal(const string& input, const vector<string>& users,
                       string* payload, map<string, string>* enc_session);

  DBManagerClient* dbm_;

  DISALLOW_COPY_AND_ASSIGN(Encryptor);
};

} // namespace lockbox
