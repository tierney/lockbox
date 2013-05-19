#include "compressor.h"

#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>


namespace lockbox {
// #include <iostream>
// #include <fstream>
// #include <boost/iostreams/filtering_stream.hpp>
// #include <boost/iostreams/filter/gzip.hpp>
// int main()
// {
//     std::ifstream file("file.gz", std::ios_base::in | std::ios_base::binary);
//     try {
//         boost::iostreams::filtering_istream in;
//         in.push(boost::iostreams::gzip_decompressor());
//         in.push(file);
//         for(std::string str; std::getline(in, str); )
//         {
//             std::cout << "Processed line " << str << '\n';
//         }
//     }
//     catch(const boost::iostreams::gzip_error& e) {
//          std::cout << e.what() << '\n';
//     }
// }

void Gzip::Compress(const string& input, string* output) {
  CHECK(output);
  boost::iostreams::filterting_istream in;
  in.push(boost::iostreams::gzip_decompressor());
  in.push(input);
  std::stringstream ssout;
  boost::iostreams::copy(in, ssout);
  *output = ssout.str();
}

void Gzip::Decompress(const string& input, string* output) {
  CHECK(output);

  boost::iostreams::filterting_istream in;
  in.push(boost::iostreams::gzip_compressor());
  in.push(input);
  std::stringstream ssout;
  boost::iostreams::copy(in, ssout);
  *output = ssout.str();
}

} // namespace lockbox
