#include "block_cipher.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <openssl/aes.h>
#include <openssl/rand.h>

namespace lockbox {

BlockCipher::BlockCipher()
      : encrypt_(EVP_CIPHER_CTX_new()),
        decrypt_(EVP_CIPHER_CTX_new()),
        cipher_(EVP_aes_256_cbc()),
        digest_(EVP_md5()),
        salt_(new unsigned char[kSaltLen]),
        iv_(new unsigned char[EVP_MAX_IV_LENGTH]),
        key_(new unsigned char[EVP_MAX_KEY_LENGTH]),
        nrounds_(1) {

  EVP_CIPHER_CTX_init(encrypt_.get());
  EVP_CIPHER_CTX_init(decrypt_.get());

  bzero(salt_.get(), kSaltLen);
  bzero(iv_.get(), EVP_MAX_IV_LENGTH);
  bzero(key_.get(), EVP_MAX_KEY_LENGTH);
}

BlockCipher::~BlockCipher() {
  EVP_CIPHER_CTX_cleanup(encrypt_.get());
  EVP_CIPHER_CTX_cleanup(decrypt_.get());
}

template< typename T >
std::string int_to_hex( T i ) {
  std::stringstream stream;
  stream << ""                          // May want to prepend 0x.
         << std::setfill ('0') << std::setw(sizeof(T)*2)
         << std::hex << i;
  return stream.str();
}

void BlockCipher::PrintSalt() const {
  for (int i = 0; i < kSaltLen; i++) {
    std::cout << int_to_hex<int>(salt_[i]) << " ";
  }
  std::cout << std::endl;
}

void BlockCipher::PrintKey() const {
   for (int i = 0; i < EVP_MAX_KEY_LENGTH; i++) {
    std::cout << int_to_hex<int>(key_[i]) << " ";
  }
  std::cout << std::endl;
}


bool BlockCipher::Encrypt(const std::string& input,
                          const std::string& password,
                          std::string* output) {
  assert(output != NULL);

  // encrypt_.reset(EVP_CIPHER_CTX_new());
  // bzero(salt_.get(), kSaltLen);
  // bzero(iv_.get(), EVP_MAX_IV_LENGTH + 1);
  // bzero(key_.get(), EVP_MAX_KEY_LENGTH + 1);

  RAND_bytes(salt_.get(), 8);

  EVP_BytesToKey(cipher_,
                 digest_,
                 salt_.get(),
                 reinterpret_cast<const unsigned char*>(password.c_str()),
                 password.length(),
                 nrounds_,
                 key_.get(),
                 iv_.get());

  EVP_EncryptInit_ex(encrypt_.get(),
                     cipher_,
                     NULL,
                     key_.get(),
                     iv_.get());

  int c_len = input.length() + 1 + AES_BLOCK_SIZE;
  int f_len = 0;

  scoped_array<unsigned char> ciphertext(new unsigned char[c_len + 1]);
  bzero(ciphertext.get(), c_len + 1);

  EVP_EncryptInit_ex(encrypt_.get(), NULL, NULL, NULL, NULL);

  /* update ciphertext, c_len is filled with the length of ciphertext generated,
   *len is the size of plaintext in bytes */
  EVP_EncryptUpdate(encrypt_.get(),
                    ciphertext.get(),
                    &c_len,
                    reinterpret_cast<const unsigned char *>(input.c_str()),
                    input.length());

  /* update ciphertext with the final remaining bytes */
  EVP_CipherFinal_ex(encrypt_.get(), ciphertext.get() + c_len, &f_len);

  // OpenSSL format. Magic number is "Salted__" followed by the salt and then
  // the ciphertext.
  output->clear();
  output->append("Salted__");
  output->append(reinterpret_cast<const char *>(salt_.get()),
                 kSaltLen);
  output->append(reinterpret_cast<const char *>(ciphertext.get()),
                 c_len + f_len);
  return true;
}

bool BlockCipher::Decrypt(const std::string& input,
                          const std::string& password,
                          std::string* output) {
  assert(output != NULL);

  // decrypt_.reset(EVP_CIPHER_CTX_new());
  // bzero(salt_.get(), kSaltLen);
  // bzero(iv_.get(), EVP_MAX_IV_LENGTH + 1);
  // bzero(key_.get(), EVP_MAX_KEY_LENGTH + 1);

  int p_len = input.length() - 16, f_len = 0;
  scoped_array<unsigned char> plaintext(new unsigned char[p_len + AES_BLOCK_SIZE + 1]);
  bzero(plaintext.get(), p_len + AES_BLOCK_SIZE + 1);

  // Parse the input string for iv and ciphertext.
  bzero(salt_.get(), 8);
  memcpy(reinterpret_cast<char *>(salt_.get()), input.substr(8, 8).c_str(), 8);

  EVP_BytesToKey(cipher_,
                 digest_,
                 salt_.get(),
                 reinterpret_cast<const unsigned char*>(password.c_str()),
                 password.length(),
                 nrounds_,
                 key_.get(),
                 iv_.get());


  EVP_DecryptInit_ex(decrypt_.get(), cipher_, NULL, key_.get(), iv_.get());

  scoped_array<unsigned char> input_ctx(new unsigned char[p_len]);
  memcpy(reinterpret_cast<char *>(input_ctx.get()), input.substr(16).c_str(), p_len);

  int len = p_len;
  EVP_DecryptUpdate(decrypt_.get(),
                    plaintext.get(),
                    &p_len,
                    reinterpret_cast<const unsigned char *>(input_ctx.get()),
                    len);
  EVP_DecryptFinal_ex(decrypt_.get(),
                      plaintext.get() + p_len,
                      &f_len);

  output->clear();
  output->append(reinterpret_cast<const char *>(plaintext.get()), p_len + f_len);

  return true;
}

} // namespace lockbox
