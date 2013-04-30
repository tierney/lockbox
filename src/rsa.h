 // lockbox::RSAPEM rsa;
  // string priv;
  // string pub;
  // rsa.Generate("passphrase", &priv, &pub);

  // string enc;
  // rsa.PublicEncrypt(pub, "0123456789012345678901", &enc);

  // string dec;
  // rsa.PrivateDecrypt(priv, enc, &dec);
  // LOG(INFO) << dec;

#pragma once

#include <string>
#include <exception>

#include "base/memory/scoped_ptr.h"

#include <openssl/rsa.h>
#include <openssl/pem.h>

using std::string;

namespace lockbox {

class RSAWrapper {
 public:
  static void Encrypt(const string& input, RSA* rsa, string* out);

  static void Decrypt(const string& input, RSA* rsa, string* out);
 private:
};

class RSAPEM {
 public:
  RSAPEM();

  virtual ~RSAPEM();

  void Generate(const string& passphrase, string* priv_pem, string* pub_pem);

  void PublicEncrypt(const string& pem, const string& input, string* output);

  void PrivateDecrypt(const string& pem, const string& input, string* output);
};

} // namespace lockbox
