#include "encryptor.h"

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/sha1.h"
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
#include "hash_util.h"

using std::string;
using std::vector;

namespace lockbox {

Encryptor::Encryptor(Client* client, DBManagerClient* dbm, UserAuth* user_auth)
    : client_(client), dbm_(dbm), user_auth_(user_auth) {
  CHECK(client);
  CHECK(dbm);
  CHECK(user_auth);
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
  package->path.data_sha1 = SHA1Hex(package->path.data);

  CHECK(success);

  // Encrypt the data.
  success = EncryptInternal(raw_input, users, &(package->payload.data),
                            &(package->payload.user_enc_session));
  package->payload.data_sha1 = SHA1Hex(package->payload.data);

  CHECK(success);
  return true;
}


bool Encryptor::EncryptInternal(
    const string& raw_input, const vector<string>& emails,
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
  for (const string& email : emails) {
    string key;
    dbm_->Get(email_key_options, email, &key);
    if (key.empty()) {
      LOG(INFO) << "Going to the cloud for the user's key " << email;
      PublicKey pub;
      client_->Exec<void, PublicKey&, const string&>(
          &LockboxServiceClient::GetKeyFromEmail, pub, email);
      key = pub.key;
    }
    CHECK(!key.empty()) << "Could not find user's key anywhere " << email;

    string enc_session;
    RSAPEM rsa_pem;
    LOG(INFO) << "Encrypting for " << email;
    rsa_pem.PublicEncrypt(key, password, &enc_session);

    user_enc_session->insert(std::make_pair(email, enc_session));
}

  return true;
}

bool Encryptor::Decrypt(const string& data,
                        const map<string, string>& user_enc_session,
                        string* output) {
  CHECK(output);
  string encrypted_key = user_enc_session.find(user_auth_->email)->second;
  CHECK(!encrypted_key.empty());

  DBManagerClient::Options client_data_options;
  client_data_options.type = ClientDB::CLIENT_DATA;

  string priv_key;
  dbm_->Get(client_data_options, "PRIV_KEY", &priv_key);
  CHECK(!priv_key.empty());

  RSAPEM rsa_pem;
  string out;
  LOG(WARNING) << "Using user auth password for PEM password. Correct?";
  rsa_pem.PrivateDecrypt(user_auth_->password, priv_key, encrypted_key, &out);
  CHECK(!out.empty());

  BlockCipher block_cipher;
  CHECK(block_cipher.Decrypt(data, out, output));

  return true;
}

bool Encryptor::HybridDecrypt(const HybridCrypto& hybrid,
                              string* output) {
  return Decrypt(hybrid.data, hybrid.user_enc_session, output);
}

} // namespace lockbox
