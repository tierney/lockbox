#pragma once

#include <string>
#include <iostream>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "crypto/rsa_private_key.h"
#include "gflags/gflags.h"

DECLARE_string(config_dir);

const int k2048BitKey = 2048;

namespace lockbox {

class LocalInitialization {
 public:
  LocalInitialization(const std::string& directory)
      : num_bits_(k2048BitKey),
        top_dir_(directory),
        config_dir_(FLAGS_config_dir) {
  }

  virtual ~LocalInitialization() {
  }


  void Run() {
    InitDirectory();
    std::cout << "Created directories..." << std::endl;
    InitCrypto();
  }

 private:
  void InitDirectory();
  void InitCrypto();

  uint16 num_bits_;
  scoped_ptr<crypto::RSAPrivateKey> private_key_;

  base::FilePath top_dir_;
  base::FilePath config_dir_;
  DISALLOW_COPY_AND_ASSIGN(LocalInitialization);
};


} // namespace lockbox
