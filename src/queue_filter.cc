#include "queue_filter.h"

#include <algorithm>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_split.h"

using std::string;
using std::vector;

namespace lockbox {

namespace {

bool IsPrefixOf(const string& first, const string& second) {
  auto res = std::mismatch(first.begin(), first.end(), second.begin());
  return (res.first == first.end());
}

} // namespace

QueueFilter::QueueFilter(DBManagerClient* dbm)
    : dbm_(dbm),
      thread_(new boost::thread(boost::bind(&QueueFilter::Run, this))) {
}

QueueFilter::~QueueFilter() {
}

void QueueFilter::Run() {
  DBManagerClient::Options unfiltered_queue_options;
  unfiltered_queue_options.type = ClientDB::UNFILTERED_QUEUE;

  while (true) {
    // Read the key from the queue.
    leveldb::DB* db = dbm_->db(unfiltered_queue_options);

    scoped_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));
    it->SeekToFirst();
    if (!it->Valid()) {
      sleep(1);
      continue;
    }
    const string ts_path = it->key().ToString();
    const string value = it->value().ToString();

    vector<string> path_state;
    base::SplitString(value, ':', &path_state);
    const string path = path_state[0];
    const string state = path_state[1];

    // Match the value to the update_queue for the appropriate TDN. We
    // accomplish this task by iterating over the keys/values of the
    // TOP_DIR_LOCATION in order to map the location string to the path. We want
    // to see that the location string is a prefix of the location.
    DBManagerClient::Options top_dir_loc_options;
    top_dir_loc_options.type = ClientDB::TOP_DIR_LOCATION;
    leveldb::DB* top_dir_loc = dbm_->db(top_dir_loc_options);
    it.reset(top_dir_loc->NewIterator(leveldb::ReadOptions()));
    string top_dir_num;
    // TODO(tierney): Cache this information.
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
      if (IsPrefixOf(it->value().ToString(), path)) {
        // Signal that we found the prefix (top directory) and extract the top
        // directory number for the database manager.
        top_dir_num = it->key().ToString();
        break;
      }
    }
    CHECK(!top_dir_num.empty()) << path;

    DBManagerClient::Options update_queue_options;
    update_queue_options.type = ClientDB::UPDATE_QUEUE_CLIENT;
    update_queue_options.name = top_dir_num;

    DBManagerClient::Options file_changes_options;
    file_changes_options.type = ClientDB::FILE_CHANGES;
    file_changes_options.name = top_dir_num;

    // Figure out if the update should be written (still see a request in the
    // queue).


    // Write to the update_queue, if necessary.
    LOG(INFO) << "Putting " << path << " into the update queue";
    dbm_->Put(update_queue_options, path, state);

    // Delete the key when done.
    dbm_->Delete(unfiltered_queue_options, ts_path);
  }
}

} // namespace lockbox
