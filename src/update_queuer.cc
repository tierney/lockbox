#include "update_queuer.h"

namespace lockbox {

UpdateQueuer::UpdateQueuer(DBManagerServer* dbm, Sync* sync)
    : dbm_(dbm), sync_(sync) {
}

UpdateQueuer::~UpdateQueuer() {
}

void UpdateQueuer::Increment() {
  LOG(INFO) << "Adding another thread.";
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
  LOG(INFO) << "Starting the thread.";
  try {
    unique_lock<mutex> lock(sync_->m, std::defer_lock);
    while (true) {

      lock.lock();

      DBManagerServer::Options options;
      options.type = ServerDB::UPDATE_ACTION_QUEUE;
      leveldb::DB* db = dbm_->db(options);
      leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
      it->SeekToFirst();

      if (!it->Valid()) {
        LOG(INFO) << "Waiting to work";
        sync_->cv.wait(lock);
        continue;
      }

      string tuple = it->key().ToString();

      // Write to timestamped leveldb.
      options.type = ServerDB::UPDATE_ACTION_LOG;
      dbm_->Put(options, tuple, "");

      // Remove old key.
      db->Delete(leveldb::WriteOptions(), tuple);

      lock.unlock();

      // Update appropriate queues with the |tuple|'s information.
      LOG(INFO) << "Update the queues from here.";

      boost::this_thread::interruption_point();
      usleep(100000);
    }
  } catch (boost::thread_interrupted&) {
    LOG(INFO) << "Done.";
  } catch (std::exception& e) {
    LOG(FATAL) << "Unknown exception " << e.what();
  }
}

} // namespace lockbox
