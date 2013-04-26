#!/usr/bin/env python

import sys
import re

kHeaderBase = """#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"

using std::string;

namespace lockbox {

class %(klass)sDB {
 public:
  explicit %(klass)sDB(const string& db_location);

  virtual ~%(klass)sDB();

 private:
  // Pointer the database. Must be deleted when we destroy this context.
  leveldb::DB* db_;

  // Database location used for connecting to leveldb.
  string db_location_;
};

} // namespace lockbox
"""

kHeaderTDNBase = """#pragma once

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"

using std::map;
using std::string;

namespace lockbox {

class %(klass)sDB {
 public:
  explicit %(klass)sDB(const string& db_location_base);

  virtual ~%(klass)sDB();

  // Used to start tracking an appropriate database name. |top_dir| is appended
  // as a directory name to the |db_location_base_| for the location of the
  // tracked database.
  bool Track(const string& top_dir);

 private:
  // Get directory database.
  leveldb::DB* GetTopDirDB(const string& top_dir);

  // Database location used for connecting to leveldb.
  string db_location_base_;

  // Map between the top directory name and the database objects.
  map<string, leveldb::DB*> top_dir_db_;
};

} // namespace lockbox
"""


kImplBase = """#include "db_%(fname)s.h"

#include "leveldb_util.h"

namespace lockbox {

%(klass)sDB::%(klass)sDB(const string& db_location)
    : db_location_(db_location) {
  db_ = OpenDB(db_location);
}

%(klass)sDB::~%(klass)sDB() {
  delete db_;
}

} // namespace lockbox
"""

kImplTDNBase = """#include "db_%(fname)s.h"

#include "base/stl_util.h"
#include "base/stringprintf.h"
#include "leveldb_util.h"

namespace lockbox {

%(klass)sDB::%(klass)sDB(const string& db_location_base)
    : db_location_base_(db_location_base) {
}

%(klass)sDB::~%(klass)sDB() {
  STLDeleteContainerPairSecondPointers(top_dir_db_.begin(), top_dir_db_.end());
}

bool %(klass)sDB::Track(const string& top_dir) {
  CHECK(!ContainsKey(top_dir_db_, top_dir));
  const string new_db_location =
      base::StringPrintf("%%s/%%s", db_location_base_.c_str(), top_dir.c_str());
  leveldb::DB* new_db = OpenDB(new_db_location);
  CHECK(new_db);
  top_dir_db_[top_dir] = new_db;
  return true;
}

leveldb::DB* %(klass)sDB::GetTopDirDB(const string& top_dir) {
  auto iter = top_dir_db_.find(top_dir);
  if (iter == top_dir_db_.end()) {
    return NULL;
  }
  return iter->second;
}

} // namespace lockbox
"""


kAutomakeBase = """noinst_LTLIBRARIES += libdb_%(fname)s.la
libdb_%(fname)s_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_%(fname)s_la_SOURCES = db_%(fname)s.h
libdb_%(fname)s_la_SOURCES += db_%(fname)s.cc
"""

def main(argv):
  print "BE VERY CAREFUL -- you must look at the code."
  return 0
  classes = [
    # ('user_device', 'UserDevice'),
    # ('device_sync', 'DeviceSync'),
    # ('user_top_dir', 'UserTopDir'),
    # ('email_key', 'EmailKey'),
    # ('top_dir_meta', 'TopDirMeta'),
    # ('top_dir_relpath_lock', 'TopDirRelpathLock'),
    # ('top_dir_snaps', 'TopDirSnaps'),
    # ('top_dir_data', 'TopDirData'),
    # ('top_dir_fptrs', 'TopDirFptrs')]
  for fname, klass in classes:
    # Create the .h and .cc files.
    with open('db_' + fname + '.gen.h','w') as fh:
      fh.write(kHeaderTDNBase % {'klass': klass, 'fname': fname})
    with open('db_' + fname + '.gen.cc','w') as fh:
      fh.write(kImplTDNBase % {'klass': klass, 'fname': fname})

    # Generate the automake contents.
    print kAutomakeBase % {'fname': fname}

if __name__=='__main__':
  main(sys.argv)
