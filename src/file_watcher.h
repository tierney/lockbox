#pragma once

#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/memory/weak_ptr.h"

#include "negotiator.h"

namespace lockbox {

class FileWatcher : public base::RefCountedThreadSafe<FileWatcher> {
 public:
  FileWatcher(Negotiator* negotiator)
      : negotiator_(negotiator),
        file_thread_("FileWatcher"),
        weak_factory_(this) {
    CHECK(negotiator);
    file_watcher_callback_ =
        base::Bind(&FileWatcher::HandleFileWatchNotification,
                   weak_factory_.GetWeakPtr());
  }

  ~FileWatcher() {
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
        base::Bind(&FileWatcher::SetupWatchCallback,
                   this,
                   target, watcher, &result, &completion));
    completion.Wait();
    return result;

  }

  bool RemoveWatch() {
    return true;
  }

  void SetupWatchCallback(const base::FilePath& target,
                          base::FilePathWatcher* watcher,
                          bool* result,
                          base::WaitableEvent* completion) {
    *result = watcher->Watch(
        target, false,
        base::Bind(&FileWatcher::HandleFileWatchNotification,
                   this));
    completion->Signal();
  }


  void HandleFileWatchNotification(const base::FilePath& path,
                                   bool got_error) {
    std::string message(got_error ? " error" : " ok");
    std::cout << path.value() << message << std::endl;
    negotiator_->QueueFile(path.value());
    negotiator_->PrintQueue();
  }

 private:
  MessageLoop loop_;

  Negotiator* negotiator_;
  base::Thread file_thread_;
  base::FilePathWatcher::Callback file_watcher_callback_;

  base::WeakPtrFactory<FileWatcher> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(FileWatcher);
};

} // namespace lockbox
