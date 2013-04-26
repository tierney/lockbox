#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

#include "base/run_loop.h"
#include "base/at_exit.h"
#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/hash_tables.h"
#include "base/files/file_path_watcher.h"
#include "base/threading/thread.h"
#include "base/memory/weak_ptr.h"
#include "base/file_util.h"
#include "gflags/gflags.h"
#include "base/synchronization/waitable_event.h"
#include "base/platform_file.h"

#include "file_watcher.h"
#include "client_initialization.h"

DEFINE_string(sync_dir, "", "Directory to sync.");
DEFINE_string(config_dir, "", "Directory with config.");
DEFINE_string(email, "", "User's email address.");

namespace lockbox {

void BlockingFileWatcherStart() {
  lockbox::LocalInitialization init_driver(FLAGS_sync_dir);
  init_driver.Run();

  // base::Thread* lockbox_thread = new base::Thread("Lockbox Thread");
  // base::Thread::Options thread_options;
  // thread_options.message_loop_type = MessageLoop::TYPE_IO;
  // CHECK(lockbox_thread->StartWithOptions(thread_options));

  base::hash_map<std::string, base::FilePathWatcher*> path_watchers;
  base::FilePath watch_path(FLAGS_sync_dir);
  base::FilePathWatcher fpw;

  lockbox::Negotiator neg;
  lockbox::FileWatcher fw(&neg);
  fw.Init();
  fw.SetupWatch(base::FilePath(FLAGS_sync_dir), &fpw);
  fw.WaitForEvents();
}

} // namespace lockbox

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);
  base::AtExitManager exit_manager;

  // Calls the example code above so that we can start monitoring a directory.
  // lockbox::BlockingFileWatcherStart();



  return 0;
}
