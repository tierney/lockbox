#include "client_initialization.h"

#include <fstream>
#include <iostream>
#include <ostream>

#include "base/file_util.h"
#include "base/logging.h"
#include "base/stringprintf.h"

namespace lockbox {

void LocalInitialization::InitDirectory() {
  CHECK(top_dir_.IsAbsolute()) << top_dir_.value();
  CHECK(file_util::CreateDirectory(top_dir_));
}

void LocalInitialization::InitCrypto() {
  CHECK(config_dir_.IsAbsolute()) << config_dir_.value();
  CHECK(file_util::CreateDirectory(config_dir_));

  private_key_.reset(crypto::RSAPrivateKey::Create(num_bits_));
  CHECK(private_key_.get());

  std::vector<uint8> private_key;
  CHECK(private_key_->ExportPrivateKey(&private_key));

  std::vector<uint8> public_key;
  CHECK(private_key_->ExportPublicKey(&public_key));

  //base::StringPrintf("%s/key", config_dir_.value().c_str()).c_str(),
  std::ofstream outfile(
      config_dir_.Append("key").value().c_str(),
      std::ios::out | std::ios::binary);
  outfile.write(reinterpret_cast<const char *>(&private_key[0]),
                private_key.size());

  std::ofstream outfile_pub(
      base::StringPrintf("%s/key.pub",
                         config_dir_.value().c_str()).c_str(),
      std::ios::out | std::ios::binary);
  outfile_pub.write(reinterpret_cast<const char *>(&public_key[0]),
                    public_key.size());

}

} // namespace lockbox
