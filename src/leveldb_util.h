#pragma once

#include <string>
#include "leveldb/db.h"

namespace lockbox {

leveldb::DB* OpenDB(const std::string& db_location);

} // namespace lockbox
