#pragma once

#include <string>
#include "leveldb/db.h"

using std::string;

namespace lockbox {

leveldb::DB* OpenDB(const string& db_location);

} // namespace lockbox
