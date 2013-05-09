#include "encryptor.h"

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "crypto/random.h"
#include "crypto/encryptor.h"
#include "crypto/rsa_private_key.h"
#include "crypto/symmetric_key.h"
#include "crypto/openssl_util.h"
#include "base/file_util.h"
#include "block_cipher.h"
#include "rsa_public_key_openssl.h"
#include "rsa.h"
#include "util.h"

using std::string;
using std::vector;

namespace lockbox {

Encryptor::Encryptor(DBManagerClient* dbm)
    : dbm_(dbm) {
  CHECK(dbm);
}

Encryptor::~Encryptor() {
}

bool Encryptor::Encrypt(const string& top_dir_path, const string& path,
                        const vector<string>& users, RemotePackage* package) {
  // Read file to string.
  string raw_input;
  file_util::ReadFileToString(base::FilePath(path), &raw_input);

  return EncryptString(top_dir_path, path, raw_input, users, package);
}


bool Encryptor::EncryptString(const string& top_dir_path,
                              const string& path,
                              const string& raw_input,
                              const vector<string>& users,
                              RemotePackage* package) {
  CHECK(package);
  bool success = false;

  // Encrypt the relative path name.
  string rel_path(RemoveBaseFromInput(top_dir_path, path));
  success = EncryptInternal(rel_path, users, &(package->path.data),
                            &(package->path.user_enc_session));
  CHECK(success);

  // Encrypt the data.
  success = EncryptInternal(raw_input, users, &(package->payload.data),
                            &(package->payload.user_enc_session));
  CHECK(success);
  return true;
}


bool Encryptor::EncryptInternal(
    const string& raw_input, const vector<string>& users,
    string* data, map<string, string>* user_enc_session) {
  CHECK(data);
  CHECK(user_enc_session);

   // Encrypt the file with the session key.
  char password_bytes[22];
  memset(password_bytes, '\0', 22);
  crypto::RandBytes(password_bytes, 21);
  string password(password_bytes);
  // LOG(INFO) << "Password " << password;

  // Cipher the main payload data with the symmetric key algo.
  BlockCipher block_cipher;
  data->clear();
  CHECK(block_cipher.Encrypt(raw_input, password, data));

  // Encrypt the session key per user using RSA.
  DBManagerClient::Options email_key_options;
  email_key_options.type = ClientDB::EMAIL_KEY;
  for (const string& user : users) {
    string key;
    dbm_->Get(email_key_options, user, &key);

    string enc_session;
    RSAPEM rsa_pem;
    rsa_pem.PublicEncrypt(key, password, &enc_session);

    user_enc_session->insert(std::make_pair(user, enc_session));
}

  return true;
}

bool Encryptor::Decrypt(const string& data,
                        const map<string, string>& user_enc_session,
                        string* output) {
  CHECK(output);
  string encrypted_key = user_enc_session.find("me2@you.com")->second;
  CHECK(!encrypted_key.empty());

  DBManagerClient::Options client_data_options;
  client_data_options.type = ClientDB::CLIENT_DATA;

  string priv_key;
  dbm_->Get(client_data_options, "PRIV_KEY", &priv_key);

  RSAPEM rsa_pem;
  string out;
  rsa_pem.PrivateDecrypt("password", priv_key, encrypted_key, &out);

  BlockCipher block_cipher;
  block_cipher.Decrypt(data, out, output);
  LOG(INFO) << "Decrypted out: " << *output;

  return false;
}

} // namespace lockbox
