#include <bzlib.h>
#include <zlib.h>

namespace lockbox {

// Model for the use of zlib.h to compress data.
// void UniquePosition::ToProto(sync_pb::UniquePosition* proto) const {
//   proto->Clear();
//   if (bytes_.size() < kCompressBytesThreshold) {
//     // If it's small, then just write it.  This is the common case.
//     proto->set_value(bytes_);
//   } else {
//     // We've got a large one.  Compress it.
//     proto->set_uncompressed_length(bytes_.size());
//     std::string* compressed = proto->mutable_compressed_value();
//
//     uLongf compressed_len = compressBound(bytes_.size());
//     compressed->resize(compressed_len);
//     int result = compress(reinterpret_cast<Bytef*>(string_as_array(compressed)),
//              &compressed_len,
//              reinterpret_cast<const Bytef*>(bytes_.data()),
//              bytes_.size());
//     if (result != Z_OK) {
//       NOTREACHED() << "Failed to compress position: " << result;
//       // Maybe we can write an uncompressed version?
//       proto->Clear();
//       proto->set_value(bytes_);
//     } else if (compressed_len >= bytes_.size()) {
//       // Oops, we made it bigger.  Just write the uncompressed version instead.
//       proto->Clear();
//       proto->set_value(bytes_);
//     } else {
//       // Success!  Don't forget to adjust the string's length.
//       compressed->resize(compressed_len);
//     }
//   }
// }

// static
// This implementation is based on the Firefox MetricsService implementation.
bool Compressor::Bzip2Compress(const std::string& input,
                               std::string* output) {
  bz_stream stream = {0};
  // As long as our input is smaller than the bzip2 block size, we should get
  // the best compression.  For example, if your input was 250k, using a block
  // size of 300k or 500k should result in the same compression ratio.  Since
  // our data should be under 100k, using the minimum block size of 100k should
  // allocate less temporary memory, but result in the same compression ratio.
  int result = BZ2_bzCompressInit(&stream,
                                  1,   // 100k (min) block size
                                  0,   // quiet
                                  0);  // default "work factor"
  if (result != BZ_OK) {  // out of memory?
    return false;
  }

  output->clear();

  stream.next_in = const_cast<char*>(input.data());
  stream.avail_in = static_cast<int>(input.size());
  // NOTE: we don't need a BZ_RUN phase since our input buffer contains
  //       the entire input
  do {
    output->resize(output->size() + 1024);
    stream.next_out = &((*output)[stream.total_out_lo32]);
    stream.avail_out = static_cast<int>(output->size()) - stream.total_out_lo32;
    result = BZ2_bzCompress(&stream, BZ_FINISH);
  } while (result == BZ_FINISH_OK);
  if (result != BZ_STREAM_END) {  // unknown failure?
    output->clear();
    // TODO(jar): See if it would be better to do a CHECK() here.
    return false;
  }
  result = BZ2_bzCompressEnd(&stream);
  DCHECK(result == BZ_OK);

  output->resize(stream.total_out_lo32);

  return true;
}

} // namespace lockbox
