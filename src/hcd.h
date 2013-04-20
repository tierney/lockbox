#pragma once

#include <string>

using std::string;

namespace lockbox {

// Defines the type of DigestFunction.
typedef unsigned char (*DigestFunctionPtr)(const unsigned char* d,
                                           unsigned long n,
                                           unsigned char* md);

class HashChainDigest {
 public:
  HashChainDigest(DigestFunctionPtr digest);

  ~HashChainDigest();

  string ComputeNext(const string& n_minus_1, const string& message);

 private:
  DigestFunctionPtr digest_;

};

}
