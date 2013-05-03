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

using std::string;
using std::vector;

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
  memset(password_bytes, 'a', 21);
  password_bytes[21] = '\0';

  // memset(password_bytes, '\0', 22);
  // crypto::RandBytes(password_bytes, 21);
  string password(password_bytes);
  LOG(INFO) << "Password " << password;

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

    string out_password;
    Decrypt(*data, *user_enc_session, &out_password);
    LOG(INFO) << "out_password " << out_password;
}

  return true;
}

bool Encryptor::Decrypt(const string& data,
                        const map<string, string>& user_enc_session,
                        string* out_path) {
  CHECK(out_path);
  string encrypted_key = user_enc_session.find("me2@you.com")->second;
  CHECK(!encrypted_key.empty());

  DBManagerClient::Options client_data_options;
  client_data_options.type = ClientDB::CLIENT_DATA;

  string priv_key;
  dbm_->Get(client_data_options, "PRIV_KEY", &priv_key);

  vector<uint8> key(priv_key.begin(), priv_key.end());
  crypto::RSAPrivateKey* rsa_priv_key = crypto::RSAPrivateKey::CreateFromPrivateKeyInfo(key);
  crypto::ScopedOpenSSL<RSA, RSA_free> rsa_key(RSA_new());
  crypto::ScopedOpenSSL<BIGNUM, BN_free> bn(BN_new());

  CHECK(!(!rsa_key.get() || !bn.get() || !BN_set_word(bn.get(), 65537L)));
  rsa_key.get()->n = bn.get();

  CHECK(EVP_PKEY_set1_RSA(rsa_priv_key->key(), rsa_key.get()));

  string out;
  RSAWrapper::Decrypt(encrypted_key, rsa_key.get(), &out);
  LOG(INFO) << "Decrypted session key: " << out;


  BlockCipher block_cipher;
  block_cipher.Decrypt(data, out, out_path);
  LOG(INFO) << "Decrypted out: " << *out_path;

  return false;
}

} // namespace lockbox
