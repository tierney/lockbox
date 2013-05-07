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

namespace {

bool DBEmpty(leveldb::DB* db, Sync* sync) {
  LOG(INFO) << "Checking for an empty database";
  std::unique_lock<std::mutex> lock(sync->db_mutex);
  LOG(INFO) << "Acquired the lock";
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  bool ret = !(it->Valid());
  LOG(INFO) << "Found DB to be " << ret;
  lock.unlock();
  return ret;
}

} // namespace

void UpdateQueuer::Run() {
  LOG(INFO) << "Starting the thread.";
  try {
    unique_lock<mutex> lock(sync_->cv_mutex, std::defer_lock);
    unique_lock<mutex> db_lock(sync_->db_mutex, std::defer_lock);
    while (true) {
      LOG(INFO) << "Checking if anything interesting.";
      DBManagerServer::Options options;
      options.type = ServerDB::UPDATE_ACTION_QUEUE;

      leveldb::DB* db = dbm_->db(options);
      // it->SeekToFirst();
      // if (!it->Valid()) {
      //   LOG(INFO) << "Waiting to work";
      //   sync_->cv.wait(lock);
      //   continue;
      // }

      sync_->cv.wait(lock, [&]{ return !DBEmpty(db, sync_); });

      LOG(INFO) << "Woken up...";

      db_lock.lock();
      leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
      it->SeekToFirst();
      CHECK(it->Valid());
      string tuple = it->key().ToString();
      LOG(INFO) << "Got " << tuple;

      // Write to timestamped leveldb.
      options.type = ServerDB::UPDATE_ACTION_LOG;
      dbm_->Put(options, tuple, "");

      // Remove old key.
      db->Delete(leveldb::WriteOptions(), tuple);
      db_lock.unlock();

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
