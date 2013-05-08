#include "simple_delta.h"

#include "courgette/simple_delta.h"
#include "courgette/streams.h"

namespace lockbox {

string Delta::Generate(const string& first, const string& second) {
  courgette::SourceStream old;
  old.Init(first.c_str(), first.length());

  courgette::SourceStream target;
  target.Init(second.c_str(), second.length());

  courgette::SinkStream sink;
  courgette::GenerateSimpleDelta(&old, &target, &sink);

  string output;
  output.assign(reinterpret_cast<const char*>(sink.Buffer()), sink.Length());
  return output;
}

string Delta::Apply(const string& first, const string& delta) {
  courgette::SourceStream old;
  old.Init(first.c_str(), first.length());

  courgette::SourceStream delta_stream;
  delta_stream.Init(delta.c_str(), delta.length());

  courgette::SinkStream target;
  courgette::ApplySimpleDelta(&old, &delta_stream, &target);

  string output;
  output.assign(reinterpret_cast<const char*>(target.Buffer()), target.Length());
  return output;
}

} // namespace lockbox
