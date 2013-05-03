#include "rsa.h"

#include "base/memory/scoped_ptr.h"
#include "base/logging.h"

namespace lockbox {

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

} // namespace lockbox
