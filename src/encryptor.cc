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

using std::string;

namespace lockbox {

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

  BlockCipher block_cipher;
  data->clear();
  CHECK(block_cipher.Encrypt(raw_input, password, data));

  // Encrypt the session key per user using RSA.
  scoped_ptr<crypto::RSAPrivateKey> priv_key(
      crypto::RSAPrivateKey::Create(2048));

  crypto::ScopedOpenSSL<RSA, RSA_free> rsa(
      EVP_PKEY_get1_RSA(priv_key->key()));

  // flen must be less than RSA_size(rsa)-11.
  // with 2048 modulus, then that means 32 chars, or with the padding, 21.
  int rsa_size = RSA_size(rsa.get());
  LOG(INFO) << "rsa_size: " << rsa_size;
  unsigned char* out = new unsigned char[rsa_size];
  LOG(INFO) << "password size: " << password.size();
  RSA_public_encrypt(password.size(),
                     reinterpret_cast<const unsigned char *>(password.c_str()),
                     out,
                     rsa.get(),
                     RSA_PKCS1_PADDING);

  // Must assign the whole string for the encryption output.
  string enc_session;
  enc_session.assign(reinterpret_cast<char*>(out), rsa_size);

  user_enc_session->insert(std::make_pair("me2@you.com", enc_session));

  // (*user_enc_session)["me2@you.com"] = string(reinterpret_cast<char*>(out));
  // (*user_enc_session)["hi"] = string("there");

  return true;
}

bool Encryptor::Decrypt(const string& data,
                        const map<string, string>& user_enc_session,
                        const string& out_path) {
  return true;
}

} // namespace lockbox
