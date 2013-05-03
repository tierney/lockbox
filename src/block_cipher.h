#pragma once

#include "base/memory/scoped_ptr.h"
#include <string>
#include <openssl/evp.h>

namespace lockbox {

const int kSaltLen = 8;
const int kIvLen = 32;

class BlockCipher {
 public:
  BlockCipher();

  ~BlockCipher();

  // Takes a message to be encrypted from |input| along with a human-readable
  // |password| and applies the appropriate cryptographic transformations to
  // produce an OpenSSL-compatible |output|.
  bool Encrypt(const std::string& input, const std::string& password,
               std::string* output);

  // Takes an OpenSSL-compatible |input| along with a human-readable |password|
  // and applies appropriate decryption transformations to produce the
  // byte-for-byte |output|.
  bool Decrypt(const std::string& input, const std::string& password,
               std::string* output);

  void PrintSalt() const;
  void PrintKey() const;

 private:
  void InitEncrypt(const std::string& password);
  void InitDecrypt(const std::string& input, const std::string& password);

  scoped_ptr<EVP_CIPHER_CTX> encrypt_;
  scoped_ptr<EVP_CIPHER_CTX> decrypt_;

  // Do not have ownership of these pointers.
  const EVP_CIPHER* cipher_;
  const EVP_MD* digest_;

  scoped_array<unsigned char> salt_;
  scoped_array<unsigned char> iv_;

  scoped_array<unsigned char> key_;

  int nrounds_;

  DISALLOW_COPY_AND_ASSIGN(BlockCipher);
};

} // namespace lockbox
