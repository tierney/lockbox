#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

#include "base/run_loop.h"
#include "base/at_exit.h"
#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/files/file_path_watcher.h"
#include "base/threading/thread.h"
#include "base/memory/weak_ptr.h"
#include "base/file_util.h"
#include "gflags/gflags.h"
#include "base/synchronization/waitable_event.h"

#include "client_initialization.h"

DEFINE_string(sync_dir, "", "Directory to sync.");
DEFINE_string(config_dir, "", "Directory with config.");
DEFINE_string(email, "", "User's email address.");

namespace lockbox {


class LockboxFileWatcher :
      public base::RefCountedThreadSafe<LockboxFileWatcher> {
 public:
  LockboxFileWatcher()
      : file_thread_("LockboxFileWatcher"),
        weak_factory_(this) {
    file_watcher_callback_ =
        base::Bind(&LockboxFileWatcher::HandleFileWatchNotification,
                   weak_factory_.GetWeakPtr());
  }

  ~LockboxFileWatcher() {
    base::RunLoop().RunUntilIdle();
  }

  void Init() {
    base::Thread::Options options(MessageLoop::TYPE_IO, 0);
    CHECK(file_thread_.StartWithOptions(options));
  }

  void WaitForEvents() {
    loop_.Run();
  }

  bool SetupWatch(const base::FilePath& target,
                  base::FilePathWatcher* watcher) {
    base::WaitableEvent completion(false, false);
    bool result;
    file_thread_.message_loop_proxy()->PostTask(
        FROM_HERE,
        base::Bind(&LockboxFileWatcher::SetupWatchCallback,
                   this,
                   target, watcher, &result, &completion));
    completion.Wait();
    return result;

  }

  void SetupWatchCallback(const base::FilePath& target,
                          base::FilePathWatcher* watcher,
                          bool* result,
                          base::WaitableEvent* completion) {
    *result = watcher->Watch(
        target, false,
        base::Bind(&LockboxFileWatcher::HandleFileWatchNotification,
                   this));
    completion->Signal();
  }


  void HandleFileWatchNotification(const base::FilePath& path,
                                   bool got_error) {
    std::string message(got_error ? " error" : " ok");
    std::cout << path.value() << message << std::endl;
  }

 private:
  MessageLoop loop_;
  base::Thread file_thread_;
  base::FilePathWatcher::Callback file_watcher_callback_;

  base::WeakPtrFactory<LockboxFileWatcher> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(LockboxFileWatcher);
};


} // namespace lockbox

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);

  base::AtExitManager exit_manager;

  lockbox::LocalInitialization init_driver(FLAGS_sync_dir);
  init_driver.Run();

  base::Thread* lockbox_thread = new base::Thread("Lockbox Thread");
  base::Thread::Options thread_options;
  thread_options.message_loop_type = MessageLoop::TYPE_IO;
  CHECK(lockbox_thread->StartWithOptions(thread_options));

  base::FilePath watch_path(FLAGS_sync_dir);
  base::FilePathWatcher fpw;
  lockbox::LockboxFileWatcher fw;
  fw.Init();
  fw.SetupWatch(base::FilePath(FLAGS_sync_dir), &fpw);

  // fw.Watch(watch_path,
  //          base::Bind(&lockbox::LockboxFileWatcher::HandleFileWatchNotification,
  //                     &fw));

  // lockbox::FileWatcher fw;
  // fw.Start();

  while(true) {
    sleep(1);
  }

  return 0;
}
