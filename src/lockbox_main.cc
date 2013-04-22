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
#include "base/task_runner.h"

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

class LockboxPathWatcher :
    public base::RefCountedThreadSafe<LockboxPathWatcher> {
 public:
  LockboxPathWatcher() : file_thread_("LockboxPathWatcher") {
  }

  void Init() {
    base::Thread::Options options(MessageLoop::TYPE_IO, 0);
    CHECK(file_thread_.StartWithOptions(options));
  }

  void DoSomething(const std::string& name) {
    file_thread_.message_loop()->PostTask(
        FROM_HERE, base::Bind(
            &LockboxPathWatcher::DoSomethingOnAnotherThread, this, name));
  }

  void DoSomethingOnAnotherThread(const std::string& name) {
    std::cout << "Other thread: " << name << std::endl;
  }

 private:
  // Always good form to make the destructor private so that only
  // RefCountedThreadSafe can access it.  This avoids bugs with double deletes.
  friend class base::RefCountedThreadSafe<LockboxPathWatcher>;

  ~LockboxPathWatcher() {}

  base::Thread file_thread_;

  DISALLOW_COPY_AND_ASSIGN(LockboxPathWatcher);
};


class LockboxWatcher : public base::RefCounted<LockboxWatcher> {
 public:
  class Delegate {
   public:
    virtual ~Delegate() {}

    virtual void OnConfigUpdated() = 0;
  };

  LockboxWatcher(
      scoped_refptr<base::SingleThreadTaskRunner> main_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> io_task_runner)
      : main_task_runner_(main_task_runner),
        io_task_runner_(io_task_runner),
        weak_factory_(ALLOW_THIS_IN_INITIALIZER_LIST(this)) {
    CHECK(main_task_runner_->BelongsToCurrentThread());
  }

  void Init(const std::string& fname) {
    FilePath path(fname);
    watcher_.Watch(path,
                   false,
                   base::Bind(&LockboxWatcher::WatchCallback,
                              weak_factory_.GetWeakPtr()));
  }

  void WatchCallback(const FilePath& path, bool error) {
    std::cout << "Path: " << path.value().c_str() << std::endl;
  }

 private:
  friend class base::RefCounted<LockboxWatcher>;
  virtual ~LockboxWatcher() {}

  base::WeakPtrFactory<LockboxWatcher> weak_factory_;

  FilePathWatcher watcher_;

  DISALLOW_COPY_AND_ASSIGN(LockboxWatcher);
};


class LockboxRunner {
 public:
  void SetUp() {
    scoped_refptr<AutoThreadTaskRunner> task_runner = new AutoThreadTaskRunner(
        message_loop_.message_loop_proxy(), run_loop_.QuitClosure());
    scoped_refptr<AutoThreadTaskRunner> io_task_runner =
        AutoThread::CreateWithType("IPC thread", task_runner,
                                   MessageLoop::TYPE_IO);

    watcher_.reset(new LockboxWatcher(task_runner, io_task_runner, &delegate_));
  }


 protected:
  MessageLoop message_loop_;
  base::RunLoop run_loop_;

  scoped_ptr<LockboxWatcher> watcher_;
};


int main(int argc, char** argv) {

  AtExitManager exit_manager;
  base::MessageLoopForIO message_loop;

  scoped_refptr<LockboxPathWatcher> lpw = new LockboxPathWatcher();
  lpw->Init();
  lpw->DoSomething("Otherwise");

  scoped_refptr<LockboxWatcher> lw = new LockboxWatcher();
  lw->Init(argv[1]);


  // FilePath file_path(argv[1]);
  // std::cout << "Watching " << file_path.value() << std::endl;

  // FilePathWatcher fpw;
  // message_loop.PostTask(FROM_HERE,
  //                       base::Bind(&FilePathWatcher::Watch, &fpw, file_path));

  // CHECK(fpw.Watch(file_path, false, &PrintHi, this));

  Wait();

  return 0;
}
