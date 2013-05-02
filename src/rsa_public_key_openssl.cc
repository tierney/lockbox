#include "rsa_public_key_openssl.h"

#include <openssl/bio.h>
#include <openssl/x509.h>

#include "crypto/openssl_util.h"

namespace lockbox {

RSA* RSAPublicKey::PublicKeyToRSA(const vector<uint8>& pub) {
  crypto::ScopedOpenSSL<BIO, BIO_free_all> mem(
      BIO_new_mem_buf(const_cast<unsigned char*>(&pub[0]), pub.size()));
  crypto::ScopedOpenSSL<EVP_PKEY, EVP_PKEY_free> ret(
      d2i_PUBKEY_bio(mem.get(), NULL));
  if (!ret.get())
    return NULL;
  return EVP_PKEY_get1_RSA(ret.get());
}

RSA* RSAPublicKey::PublicKeyToRSA(const string& pub) {
  return RSAPublicKey::PublicKeyToRSA(vector<uint8>(pub.begin(), pub.end()));
}

} // namespace lockbox
