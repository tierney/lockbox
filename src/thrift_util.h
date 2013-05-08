#pragma once

#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include "base/logging.h"

using std::string;

namespace lockbox {

template<typename T>
uint32_t ThriftToString(const T& pkg, string* out) {
  CHECK(out);
  boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> mem_buf(
      new apache::thrift::transport::TMemoryBuffer());
  boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> bin_prot(
      new apache::thrift::protocol::TBinaryProtocol(mem_buf));

  const uint32_t ret = pkg.write(bin_prot.get());
  out->clear();
  out->assign(mem_buf->getBufferAsString());
  return ret;
}

template<typename T>
uint32_t ThriftFromString(const string& in, T* pkg) {
  CHECK(pkg);
  boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> mem_buf(
      new apache::thrift::transport::TMemoryBuffer(
          reinterpret_cast<uint8_t*>(
              const_cast<char*>(in.c_str())), in.size()));
  boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> bin_prot(
      new apache::thrift::protocol::TBinaryProtocol(mem_buf));

  return pkg->read(bin_prot.get());
}

} // namespace lockbox
