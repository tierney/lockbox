#pragma once

#include <string>
#include <deque>

#include "base/hash_tables.h"
#include "base/stl_util.h"

using std::string;
using std::deque;
using base::hash_set;

namespace lockbox {

class Negotiator {
 public:
  Negotiator() {
  }

  virtual ~Negotiator() {
  }

  void QueueFile(const std::string& fpath) {
    if (ContainsKey(queue_set_, fpath)) {
      return;
    }
    queue_set_.insert(fpath);
    queue_.push_back(fpath);
  }

  string PopFile() {
    string ret(queue_.front());

    // Delete from queue.
    const auto& set_ret = queue_set_.find(ret);
    CHECK(set_ret != queue_set_.end());
    queue_set_.erase(set_ret);
    queue_.pop_front();

    return ret;
  }

  bool ContainsFile(const std::string& fpath) {
    return ContainsKey(indexed_paths_, fpath);
  }

  void PrintQueue() {

    for (auto& itr : queue_) {
      std::cout << " " << itr << std::endl;
    }
  }


 private:

  // Contains the list of files that we must process.
  deque<std::string> queue_;
  hash_set<std::string> queue_set_;

  // Contains the list of files that we have processed locally. The map is to
  // the latest hash value (this allows us to test for modifications in the
  // content of the file).
  base::hash_map<std::string, std::string> indexed_paths_;

  DISALLOW_COPY_AND_ASSIGN(Negotiator);
};

} // namespace lockbox
