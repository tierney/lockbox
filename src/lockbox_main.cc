#include <iostream>
#include <limits>

#include "base/bind.h"
#include "base/files/file_path_watcher.h"
#include "base/files/file_path.h"
#include "base/callback.h"
#include "base/at_exit.h"
#include "base/message_loop.h"
#include "base/threading/thread.h"
#include "base/file_util.h"

using base::FilePathWatcher;
using base::FilePath;
using base::AtExitManager;

void Wait() {
  std::cout << "Press ENTER to continue...";
  std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}


void PrintHi(const FilePath& path, bool error) {
  file_util::WriteFile(FilePath("/home/tierney/toss.log"),
                             path.value().c_str(),
                             path.value().length());
}

class LockboxPathWatcher {
 public:
  LockboxPathWatcher() : file_thread_("LockboxPathWatcher") {
  }

  void Init() {
    base::Thread::Options options(MessageLoop::TYPE_IO, 0);
    CHECK(file_thread_.StartWithOptions(options));
  }

  void Run() {
    file_thread_.Start();
  }

 private:
  base::Thread file_thread_;
  DISALLOW_COPY_AND_ASSIGN(LockboxPathWatcher);
};

int main(int argc, char** argv) {

  AtExitManager exit_manager;

  // LockboxPathWatcher lpw;
  // lpw.Init();

  base::MessageLoopForIO message_loop;
  FilePath file_path(argv[1]);
  std::cout << "Watching " << file_path.value() << std::endl;

  FilePathWatcher fpw;
  message_loop.PostTask(FROM_HERE,
                        base::Bind(&FilePathWatcher::Watch, &fpw, file_path));

  CHECK(fpw.Watch(file_path, false, &PrintHi, this));

  Wait();

  return 0;
}
