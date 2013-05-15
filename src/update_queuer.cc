#include "update_queuer.h"

#include "base/strings/string_split.h"

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
  std::unique_lock<std::mutex> lock(sync->db_mutex);
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  bool ret = !(it->Valid());
  lock.unlock();
  return ret;
}

} // namespace

void UpdateQueuer::Run() {
  try {
    unique_lock<mutex> lock(sync_->cv_mutex, std::defer_lock);
    unique_lock<mutex> db_lock(sync_->db_mutex, std::defer_lock);
    while (true) {
      DBManagerServer::Options options;
      options.type = ServerDB::UPDATE_ACTION_QUEUE;

      leveldb::DB* db = dbm_->db(options);
      sync_->cv.wait(lock, [&]{ return !DBEmpty(db, sync_); });

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
      // These will be user's device queues. We look at the TOP_DIR_META EDITORS
      // key to find the users. THen we match the user to the devices through
      // USER_DEVICE. Then the DEVICE_SYNC values are updated.

      vector<string> update;
      base::SplitString(tuple, '_', &update);
      CHECK(update.size() == 5);
      const string& ts = update[0];
      const string& top_dir = update[1];
      const string& rel_path = update[2];
      const string& uploading_device = update[3];
      const string& hash = update[4];

      // TOP_DIR_META editors.
      options.type = ServerDB::TOP_DIR_META;
      options.name = top_dir;
      string users_to_update;

      // Iterate through the EDITORS.
      vector<string> emails;
      CHECK(dbm_->GetList(options, "EDITORS", &emails));

      vector<string> user_ids;
      for (const string& email : emails) {
        string user_id;
        CHECK(dbm_->Get(
            DBManager::Options(ServerDB::EMAIL_USER, ""), email, &user_id))
            << email;
        user_ids.push_back(user_id);
      }

      // USER_DEVICE
      for (const string& user : user_ids) {
        options.type = ServerDB::USER_DEVICE;
        options.name = "";
        vector<string> devices;
        CHECK(dbm_->GetList(options, user, &devices))
            << user << " not in USER_DEVICE";

        // DEVICE_SYNC append.
        options.type = ServerDB::DEVICE_SYNC;
        options.name = "";
        for (const string& device : devices) {
          LOG(INFO) << "Device " << device << " for user " << user;
          if (device == uploading_device) {
            LOG(INFO) << "Skipping the uploading device.";
            continue;
          }

          // TODO(tierney): Lock the database entries for the prefix.
          LOG(INFO) << "Appending to device " << device << ": " << tuple;
          CHECK(dbm_->Append(options, device, tuple));
        }
      }

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
