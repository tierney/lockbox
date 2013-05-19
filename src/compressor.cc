#include "compressor.h"

#include "base/logging.h"
#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>


namespace lockbox {

void Gzip::Compress(const string& input, string* output) {
  CHECK(output);
  boost::iostreams::filtering_istream in;
  in.push(boost::iostreams::gzip_decompressor());

  std::stringstream ssin;
  ssin << input;
  in.push(ssin);

  std::stringstream ssout;
  boost::iostreams::copy(in, ssout);
  *output = ssout.str();
}

void Gzip::Decompress(const string& input, string* output) {
  CHECK(output);

  boost::iostreams::filtering_istream in;
  in.push(boost::iostreams::gzip_compressor());

  std::stringstream ssin;
  ssin << input;
  in.push(ssin);

  std::stringstream ssout;
  boost::iostreams::copy(in, ssout);
  *output = ssout.str();
}

} // namespace lockbox
