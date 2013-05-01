#include "encryptor.h"

#include <string>
#include <openssl/rsa.h>

#include "crypto/encryptor.h"
#include "crypto/rsa_private_key.h"

using std::string;

	// int rsa_size = RSA_size(rsa);
	// // ??? assert rsa_size > 12 ???
	// int block_size = rsa_size - 12;
	// size_t len = msg.size();
	// size_t blocks = len/block_size;
	// int rest = static_cast<int>(len % block_size);
	// int enc_len = 0;
	// std::vector<unsigned char> enc;
	// int curr_len = 0;

	// if (0 == rest) {
	// 	enc.resize(blocks*rsa_size + 1);
	// }
	// else {
	// 	enc.resize((blocks+1)*rsa_size + 1);
	// }

	// try {

	// 	size_t i = 0;
	// 	for (i = 0; i < blocks; i++) {

	// 	if (0 > (curr_len = RSA_public_encrypt(block_size , &msg[i*block_size], &enc[i*rsa_size], rsa, RSA_PKCS1_PADDING))) {
	// 			throw ossl::OsslException("at RSA_public_encrypt");
	// 		}


namespace lockbox {

bool Encryptor::Encrypt(const string& path, const vector<string>& users,
                        string* data, map<string, string>* user_enc_session) {
  // Read file to string.
  string raw_input;
  base::ReadFileToString(base::FilePath(path), &raw_input);

  // Generate a random session key.
  scoped_ptr<crypto::SymmetricKey> key(
      GenerateRandomKey(crypto::SymmetricKey::AES, 256));
  const string& key_data = key->key();

  char iv_raw[17];
  memset(iv_raw, '\0', 17);
  crypto::RandBytes(iv_raw, 16);
  string iv(iv_raw);

  // Encrypt the file with the session key.
  crypto::Encryptor encryptor;
  encryptor.Init(key.get(), crypto::Encryptor::CBC, iv);
  string ciphertext;
  CHECK(encryptor.Encrypt(raw_input, &ciphertext));

  // Encrypt the session key per user using RSA.
  scoped_ptr<crypto::RSAPrivateKey> priv_key(
      crypto::RSAPrivateKey::Create(2048));

  LOG(INFO) << "RSA_size " << RSA_size(priv_key.get());
  // flen must be less than RSA_size(rsa)-11.
  // with 2048 modulus, then that means 32 chars, or with the padding, 21.
  RSA_public_encrypt(key_data.size(),
                     const_cast<unsigned char *>(key_data.data), );
  // vector<

  return true;
}

} // namespace lockbox
