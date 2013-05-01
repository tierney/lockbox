#pragma once

#include "db_manager_client.h"
#include "base/logging.h"
#include <boost/thread/thread.hpp>

namespace lockbox {

class QueueFilter {
 public:
  QueueFilter(DBManagerClient* dbm);

  virtual ~QueueFilter();

  void Run();

 private:
  DBManagerClient* dbm_;

  boost::thread* thread_;

  DISALLOW_COPY_AND_ASSIGN(QueueFilter);
};

} // namespace lockbox
