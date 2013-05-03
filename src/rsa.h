// #include "base/base64.h"
// #include "crypto/rsa_private_key.h"
// #include "base/memory/scoped_ptr.h"

// int main(int argc, char** argv) {
//   base::AtExitManager exit_manager;

//   scoped_ptr<crypto::RSAPrivateKey> key(crypto::RSAPrivateKey::Create(2048));

//   std::vector<uint8> private_key_buf;
//   key->ExportPrivateKey(&private_key_buf);
//   std::string private_key_str(private_key_buf.begin(), private_key_buf.end());
//   std::string private_key_base64;
//   base::Base64Encode(private_key_str, &private_key_base64);
//   printf("%s\n", private_key_base64.c_str());

//   std::vector<uint8> public_key_buf;
//   key->ExportPublicKey(&public_key_buf);
//   std::string public_key_str(public_key_buf.begin(), public_key_buf.end());
//   std::string public_key_base64;
//   base::Base64Encode(public_key_str, &public_key_base64);
//   printf("%s\n", public_key_base64.c_str());
// }

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
  static void Generate(const string& passphrase,
                       string* priv_pem, string* pub_pem);
  static void PublicEncrypt(const string& pem, const string& input, string* output);
  static void PrivateDecrypt(const string& pem, const string& input, string* output);
};

// class ReadError : public std::exception
// {
// public:
//     virtual const char* what() const throw();
// };

// class NoKeypairLoaded : public std::exception
// {
// public:
//     virtual const char* what() const throw();
// };

// class AccessCard
// {
// public:
//     AccessCard();
//     ~AccessCard();
//     void Generate();
//     void Load(const string& pem, const string& pass);
//     void LoadPub(const string& pem, const string& pass);
//   void Encrypt(const string& input, string* output);
//   void Decrypt(const string& input, string* output);
//     void PublicKey(string& pem) const;
//     void PrivateKey(string& pem, const string& passphrase) const;

// private:
//     void CheckKey() const;

//     RSA* keypair;
// };

// class BioBox
// {
// public:
//     struct Buffer
//     {
//         void* buf;
//         int size;
//     };

//     BioBox();
//     ~BioBox();
//     void ConstructSink(const string& str);
//     void NewBuffer();
//     BIO* Bio() const;
//     Buffer ReadAll();
// private:
//     BIO* bio;
//     Buffer buf;
// };

// class EvpBox
// {
// public:
//     EvpBox(RSA* keyp);
//     ~EvpBox();
//     EVP_PKEY* Key();
// private:
//     EVP_PKEY* evpkey;
// };

// //--------------------

// const char* ReadError::what() const throw()
// {
//     return "Problem reading BIO.";
// }
// const char* NoKeypairLoaded::what() const throw()
// {
//     return "No keypair loaded.";
// }

// AccessCard::AccessCard()
//   : keypair(NULL)
// {
//     if (EVP_get_cipherbyname("aes-256-cbc") == NULL)
//         OpenSSL_add_all_algorithms();
// }
// AccessCard::~AccessCard()
// {
//     RSA_free(keypair);
// }
// void AccessCard::CheckKey() const
// {
//     if (!keypair)
//         throw NoKeypairLoaded();
// }

// void AccessCard::Generate()
// {
//     RSA_free(keypair);
//     keypair = RSA_generate_key(2048, RSA_F4, NULL, NULL);
//     CheckKey();
// }

// static char *LoseStringConst(const string& str)
// {
//     return const_cast<char*>(str.c_str());
// }
// static void* StringAsVoid(const string& str)
// {
//     return reinterpret_cast<void*>(LoseStringConst(str));
// }

// BioBox::BioBox()
//  : bio(NULL)
// {
//     buf.buf = NULL;
//     buf.size = 0;
// }
// BioBox::~BioBox()
// {
//     BIO_free(bio);
//     free(buf.buf);
// }
// void BioBox::ConstructSink(const string& str)
// {
//     BIO_free(bio);
//     bio = BIO_new_mem_buf(StringAsVoid(str), -1);
//     if (!bio)
//         throw ReadError();
// }
// void BioBox::NewBuffer()
// {
//     BIO_free(bio);
//     bio = BIO_new(BIO_s_mem());
//     if (!bio)
//         throw ReadError();
// }
// BIO* BioBox::Bio() const
// {
//     return bio;
// }
// BioBox::Buffer BioBox::ReadAll()
// {
//     buf.size = BIO_ctrl_pending(bio);
//     buf.buf = malloc(buf.size);
//     if (BIO_read(bio, buf.buf, buf.size) < 0) {
//         //if (ERR_peek_error()) {
//         //    ERR_reason_error_string(ERR_get_error());
//         //    return NULL;
//         //}
//         throw ReadError();
//     }
//     return buf;
// }

// EvpBox::EvpBox(RSA* keyp)
// {
//     evpkey = EVP_PKEY_new();
//     if (!EVP_PKEY_set1_RSA(evpkey, keyp)) {
//         throw ReadError();
//     }
// }
// EvpBox::~EvpBox()
// {
//     EVP_PKEY_free(evpkey);
// }
// EVP_PKEY* EvpBox::Key()
// {
//     return evpkey;
// }

// static int pass_cb(char* buf, int size, int rwflag, void* u)
// {
//     const string pass = reinterpret_cast<char*>(u);
//     int len = pass.size();
//     // if too long, truncate
//     if (len > size)
//         len = size;
//     pass.copy(buf, len);
//     return len;
// }
// void AccessCard::Load(const string& pem, const string& pass)
// {
//     RSA_free(keypair);
//     BioBox bio;
//     bio.ConstructSink(pem);
//     keypair = PEM_read_bio_RSAPrivateKey(bio.Bio(), NULL, pass_cb,
//                                          StringAsVoid(pass));
//     CheckKey();
// }

// void AccessCard::LoadPub(const string& pem, const string& pass) {
//   RSA_free(keypair);
//   BioBox bio;
//   bio.ConstructSink(pem);

//   keypair = PEM_read_bio_RSA_PUBKEY(bio.Bio(), NULL, pass_cb,
//                                     StringAsVoid(pass));
//   CheckKey();
// }

// void AccessCard::PublicKey(string& pem) const
// {
//     CheckKey();
//     BioBox bio;
//     bio.NewBuffer();
//     int ret = PEM_write_bio_RSA_PUBKEY(bio.Bio(), keypair);
//     if (!ret)
//         throw ReadError();
//     const BioBox::Buffer& buf = bio.ReadAll();
//     pem = string(reinterpret_cast<const char*>(buf.buf), buf.size);
// }

// void AccessCard::Encrypt(const string& input, string* output) {
//   const int rsa_size = RSA_size(keypair);
//   scoped_array<unsigned char> temp(new unsigned char[rsa_size]);
//   RSA_public_encrypt(input.size(),
//                      reinterpret_cast<const unsigned char *>(input.c_str()),
//                      temp.get(),
//                      keypair,
//                      RSA_PKCS1_PADDING);
//   output->clear();
//   output->assign(reinterpret_cast<char *>(temp.get()), rsa_size);
// }

// void AccessCard::Decrypt(const string& input, string* output) {
//   const int kPasswordSize = 22;
//   scoped_array<unsigned char> password(new unsigned char[kPasswordSize]);
//   RSA_private_decrypt(input.size(),
//                       reinterpret_cast<const unsigned char *>(input.c_str()),
//                       password.get(),
//                       keypair,
//                       RSA_PKCS1_PADDING);
//   output->clear();
//   output->assign(reinterpret_cast<char *>(password.get()), kPasswordSize);
// }

// void AccessCard::PrivateKey(string& pem, const string& passphrase) const
// {
//     CheckKey();
//     BioBox bio;
//     bio.NewBuffer();

//     EvpBox evp(keypair);
//     int ret = PEM_write_bio_PKCS8PrivateKey(bio.Bio(), evp.Key(),
//                                             EVP_aes_256_cbc(),
//                                             LoseStringConst(passphrase),
//                                             passphrase.size(), NULL, NULL);
//     if (!ret)
//         throw ReadError();
//     const BioBox::Buffer& buf = bio.ReadAll();
//     pem = string(reinterpret_cast<const char*>(buf.buf), buf.size);
// }


} // namespace lockbox
