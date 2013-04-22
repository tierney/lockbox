#include <string>

#include "courgette/simple_delta.h"
#include "courgette/streams.h"

int main(int argc, char** argv) {
  courgette::SourceStream old;
  std::string old_str("hello, world");
  old.Init(old_str.c_str(), old_str.length());

  courgette::SourceStream target;
  std::string target_str("hello, new world");
  target.Init(target_str.c_str(), target_str.length());

  courgette::SinkStream sink;

  courgette::GenerateSimpleDelta(&old, &target, &sink);

  return 0;
}
