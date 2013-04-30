#include "rsa.h"

#include "base/memory/scoped_ptr.h"
#include "base/logging.h"
#include "crypto/openssl_util.h"

namespace lockbox {

namespace {

static char *LoseStringConst(const string& str) {
  return const_cast<char*>(str.c_str());
}


static void* StringAsVoid(const string& str) {
  return reinterpret_cast<void*>(LoseStringConst(str));
}

static int pass_cb(char* buf, int size, int rwflag, void* u) {
  const string pass = reinterpret_cast<char*>(u);
  int len = pass.size();
  // if too long, truncate
  if (len > size)
    len = size;
  pass.copy(buf, len);
  return len;
}

} // namespace

void RSAWrapper::Encrypt(const string& input, RSA* rsa, string* out) {
  CHECK(rsa);
  CHECK(out);
  const int rsa_size = RSA_size(rsa);
  scoped_array<unsigned char> temp(new unsigned char[rsa_size]);
  RSA_public_encrypt(input.size(),
                     reinterpret_cast<const unsigned char *>(input.c_str()),
                     temp.get(),
                     rsa,
                     RSA_PKCS1_PADDING);
  out->clear();
  out->assign(reinterpret_cast<char *>(temp.get()), rsa_size);
}

void RSAWrapper::Decrypt(const string& input, RSA* rsa, string* out) {
  CHECK(rsa);
  CHECK(out);
  const int kPasswordSize = 21;
  LOG(INFO) << "input size " << input.size();
  scoped_array<unsigned char> password(new unsigned char[kPasswordSize]);
  RSA_private_decrypt(input.size(),
                      reinterpret_cast<const unsigned char *>(input.c_str()),
                      password.get(),
                      rsa,
                      RSA_PKCS1_PADDING);
  out->clear();
  out->assign(reinterpret_cast<char *>(password.get()), kPasswordSize);
}

RSAPEM::RSAPEM() {
  if (EVP_get_cipherbyname("aes-256-cbc") == NULL)
      OpenSSL_add_all_algorithms();
  OpenSSL_add_all_algorithms();
}

RSAPEM::~RSAPEM() {
  EVP_cleanup();
}

void RSAPEM::Generate(const string& passphrase, string* priv_pem,
                      string* pub_pem) {
  CHECK(priv_pem);
  CHECK(pub_pem);

  // Generate key.
  crypto::ScopedOpenSSL<RSA, RSA_free> key_pair(RSA_generate_key(
      2048, RSA_F4 /* 65537L */, NULL, NULL));
  CHECK(key_pair.get());
  int buf_size = -1;

  crypto::ScopedOpenSSL<BIO, BIO_free_all> bio(BIO_new(BIO_s_mem()));
  CHECK(PEM_write_bio_RSA_PUBKEY(bio.get(), key_pair.get()));

  buf_size = BIO_ctrl_pending(bio.get());
  scoped_array<char> buf(new char[buf_size]);

  CHECK(0 <= BIO_read(bio.get(), buf.get(), buf_size));
  pub_pem->clear();
  pub_pem->assign(const_cast<const char*>(buf.get()), buf_size);


  CHECK(key_pair.get());

  bio.reset(BIO_new(BIO_s_mem()));
  crypto::ScopedOpenSSL<EVP_PKEY, EVP_PKEY_free> evpkey(EVP_PKEY_new());
  CHECK(EVP_PKEY_set1_RSA(evpkey.get(), key_pair.get()));

  CHECK(PEM_write_bio_PKCS8PrivateKey(bio.get(), evpkey.get(),
                                      EVP_aes_256_cbc(),
                                      LoseStringConst(passphrase),
                                      passphrase.size(), NULL, NULL));

  buf_size = BIO_ctrl_pending(bio.get());
  buf.reset(new char[buf_size]);

  CHECK(0 <= BIO_read(bio.get(), buf.get(), buf_size));
  priv_pem->clear();
  priv_pem->assign(const_cast<const char*>(buf.get()), buf_size);
}

void RSAPEM::PublicEncrypt(const string& pem, const string& input,
                           string* output) {
  // Get the key from the pem.
  crypto::ScopedOpenSSL<BIO, BIO_free_all> bio(
      BIO_new_mem_buf(StringAsVoid(pem), -1));
  CHECK(bio.get());

  const string passphrase("passphrase"); // TODO(tierney): Get from user.

  crypto::ScopedOpenSSL<RSA, RSA_free> key_pair(
      PEM_read_bio_RSA_PUBKEY(bio.get(), NULL, pass_cb, StringAsVoid(passphrase)));
  CHECK(key_pair.get());

  // Encrypt for the public key.
  const int rsa_size = RSA_size(key_pair.get());
  scoped_array<unsigned char> temp(new unsigned char[rsa_size]);
  RSA_public_encrypt(input.size(),
                     reinterpret_cast<const unsigned char *>(input.c_str()),
                     temp.get(),
                     key_pair.get(),
                     RSA_PKCS1_PADDING);

  output->clear();
  output->assign(reinterpret_cast<char *>(temp.get()), rsa_size);
}

void RSAPEM::PrivateDecrypt(const string& pem, const string& input,
                            string* output) {
  // Get the key from the pem.
  crypto::ScopedOpenSSL<BIO, BIO_free_all> bio(
      BIO_new_mem_buf(StringAsVoid(pem), -1));
  CHECK(bio.get());

  const string passphrase("passphrase"); // TODO(tierney): Get from user.

  crypto::ScopedOpenSSL<RSA, RSA_free> key_pair(
      PEM_read_bio_RSAPrivateKey(bio.get(), NULL, pass_cb,
                                 StringAsVoid(passphrase)));
  CHECK(key_pair.get());

  const int kPasswordSize = 22;
  scoped_array<unsigned char> password(new unsigned char[kPasswordSize]);
  RSA_private_decrypt(input.size(),
                      reinterpret_cast<const unsigned char *>(input.c_str()),
                      password.get(),
                      key_pair.get(),
                      RSA_PKCS1_PADDING);
  output->clear();
  output->assign(reinterpret_cast<char *>(password.get()), kPasswordSize);
}

} // namespace lockbox
