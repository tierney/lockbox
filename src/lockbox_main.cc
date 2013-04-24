#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

#include "base/at_exit.h"
#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/files/file_path_watcher.h"
#include "base/threading/thread.h"
#include "base/stringprintf.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/file_util.h"
#include "crypto/rsa_private_key.h"
#include "gflags/gflags.h"

DEFINE_string(sync_dir, "", "Directory to sync.");
DEFINE_string(config_dir, "", "Directory with config.");
DEFINE_string(email, "", "User's email address.");

namespace lockbox {

const int k2048BitKey = 2048;

class LockboxFileWatcher {
 public:
  LockboxFileWatcher()
      : weak_factory_(this) {
    file_watcher_callback_ =
        base::Bind(&LockboxFileWatcher::HandleFileWatchNotification,
                   weak_factory_.GetWeakPtr());
  }

  ~LockboxFileWatcher() {
  }


  base::FilePathWatcher* Watch(const base::FilePath& watch_path,
             const base::FilePathWatcher::Callback& callback) {
    CHECK(!callback.is_null());

    base::FilePathWatcher* watcher(new base::FilePathWatcher);
    if (!watcher->Watch(watch_path, false /* recursive */, callback)) {
      delete watcher;
      return NULL;
    }
    return watcher;
  }

 private:
  void HandleFileWatchNotification(const base::FilePath& path,
                                   bool got_error) {
    CHECK(false);
  }

  base::FilePathWatcher::Callback file_watcher_callback_;

  base::WeakPtrFactory<LockboxFileWatcher> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(LockboxFileWatcher);
};

class LocalInitialization {
 public:
  LocalInitialization(const std::string& directory)
      : num_bits_(k2048BitKey),
        top_dir_(directory),
        config_dir_(FLAGS_config_dir) {
  }

  virtual ~LocalInitialization() {
  }


  void Run() {
    InitDirectory();
    InitCrypto();
  }

 private:
  void InitDirectory() {
    CHECK(top_dir_.IsAbsolute()) << top_dir_.value();
    CHECK(file_util::CreateDirectory(top_dir_));
  }

  void InitCrypto() {
    CHECK(config_dir_.IsAbsolute()) << config_dir_.value();
    CHECK(file_util::CreateDirectory(config_dir_));

    private_key_.reset(crypto::RSAPrivateKey::Create(num_bits_));
    CHECK(private_key_.get());

    std::vector<uint8> private_key;
    CHECK(private_key_->ExportPrivateKey(&private_key));

    std::vector<uint8> public_key;
    CHECK(private_key_->ExportPublicKey(&public_key));

    std::ofstream outfile(
        base::StringPrintf("%s/key", config_dir_.value().c_str()).c_str(),
        std::ios::out | std::ios::binary);
    outfile.write(reinterpret_cast<const char *>(&private_key[0]),
                  private_key.size());

    std::ofstream outfile_pub(
        base::StringPrintf("%s/key.pub",
                           config_dir_.value().c_str()).c_str(),
        std::ios::out | std::ios::binary);
    outfile_pub.write(reinterpret_cast<const char *>(&public_key[0]),
                  public_key.size());

  }

  uint16 num_bits_;
  scoped_ptr<crypto::RSAPrivateKey::RSAPrivateKey> private_key_;

  base::FilePath top_dir_;
  base::FilePath config_dir_;
  DISALLOW_COPY_AND_ASSIGN(LocalInitialization);
};

} // namespace lockbox

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);

  base::AtExitManager exit_manager;
  base::Thread* lockbox_thread = new base::Thread("Lockbox Thread");
  base::Thread::Options thread_options;
  thread_options.message_loop_type = MessageLoop::TYPE_IO;
  CHECK(lockbox_thread->StartWithOptions(thread_options));

  lockbox::LockboxFileWatcher fw;
  fw.Watch();

  // lockbox::FileWatcher fw;
  // fw.Start();
  lockbox::LocalInitialization init_driver(FLAGS_sync_dir);
  init_driver.Run();

  return 0;
}
