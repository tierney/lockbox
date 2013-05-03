#include <string>
#include <iostream>

#include "courgette/simple_delta.h"
#include "courgette/streams.h"

int main(int argc, char** argv) {
  courgette::SourceStream old;
  std::string old_str("hello, world");
  std::cout << "Old: " << old_str.length() << std::endl;
  old.Init(old_str.c_str(), old_str.length());

  courgette::SourceStream target;
  std::string target_str("hello, new world");
  std::cout << "Target: " << target_str.length() << std::endl;
  target.Init(target_str.c_str(), target_str.length());

  courgette::SinkStream sink;

  courgette::GenerateSimpleDelta(&old, &target, &sink);
  std::cout << "Size: " << sink.Length() << std::endl;
  char *buf = new char[sink.Length() + 1];
  bzero(buf, sink.Length() + 1);
  memcpy(buf, sink.Buffer(), sink.Length());
  std::cout << "Buffer: " << buf << std::endl;

  courgette::SourceStream delta;
  delta.Init(sink.Buffer(), sink.Length());

  courgette::SinkStream apply_target;
  courgette::ApplySimpleDelta(&old, &delta, &apply_target);
  std::cout << "Applied: " << apply_target.Buffer() << std::endl;

  return 0;
}
