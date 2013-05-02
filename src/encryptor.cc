#include "encryptor.h"

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>

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

using std::string;

namespace lockbox {

Encryptor::Encryptor(DBManagerClient* dbm)
    : dbm_(dbm) {
  CHECK(dbm);
}

Encryptor::~Encryptor() {
}

bool Encryptor::Encrypt(const string& path, const vector<string>& users,
                        string* data, map<string, string>* user_enc_session) {
  CHECK(data);
  CHECK(user_enc_session);

  // Read file to string.
  string raw_input;
  file_util::ReadFileToString(base::FilePath(path), &raw_input);

  // Encrypt the file with the session key.
  char password_bytes[22];
  memset(password_bytes, '\0', 22);
  crypto::RandBytes(password_bytes, 21);
  string password(password_bytes);

  // Cipher the main payload data with the symmetric key algo.
  BlockCipher block_cipher;
  data->clear();
  CHECK(block_cipher.Encrypt(raw_input, password, data));

  // Encrypt the session key per user using RSA.
  DBManagerClient::Options email_key_options;
  email_key_options.type = ClientDB::EMAIL_KEY;
  crypto::ScopedOpenSSL<RSA, RSA_free> rsa;
  for (const string& user : users) {
    string key;
    dbm_->Get(email_key_options, user, &key);
    rsa.reset(RSAPublicKey::PublicKeyToRSA(key));

    string enc_session;
    RSAWrapper::Encrypt(password, rsa.get(), &enc_session);
    user_enc_session->insert(std::make_pair(user, enc_session));
  }

  return true;
}

bool Encryptor::Decrypt(const string& data,
                        const map<string, string>& user_enc_session,
                        const string& out_path) {
  return true;
}

} // namespace lockbox
