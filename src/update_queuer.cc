#include "update_queuer.h"

namespace lockbox {

UpdateQueuer::UpdateQueuer(DBManagerServer* dbm, Sync* sync)
    : dbm_(dbm), sync_(sync) {
}

UpdateQueuer::~UpdateQueuer() {
}

void UpdateQueuer::Increment() {
  boost::thread* thread =
      new boost::thread(boost::bind(&UpdateQueuer::Run, this));
  threads_.push_back(thread);
  group_.add_thread(thread);
}

void UpdateQueuer::Decrement() {
  boost::thread* thread = threads_.back();
  group_.remove_thread(thread);
  thread->interrupt();
}

void UpdateQueuer::Run() {
  try {
    unique_lock<mutex> lock(sync_->m);
    while (true) {
      // Do something here...
      lock.lock();

      DBManagerServer::Options options;
      options.type = ServerDB::UPDATE_ACTION_QUEUE;

      string value;
      leveldb::DB* db = dbm_->db(options);
      leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
      it->SeekToFirst();
      string triple = it->key().ToString();

      if (triple.empty()) {
        sync_->cv.wait(lock);
        continue;
      }

      // Write to timestamped leveldb.

      db->Delete(leveldb::WriteOptions(), it->key());

      lock.unlock();


      // do something with |triple|.


      boost::this_thread::interruption_point();
      usleep(100000);
    }
  } catch (boost::thread_interrupted&) {
    LOG(INFO) << "Done.";
  } catch (std::exception&) {
    LOG(INFO) << "Unknown exception";
  }
}

} // namespace lockbox
