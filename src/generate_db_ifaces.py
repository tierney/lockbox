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

kAutomakeBase = """noinst_LTLIBRARIES += libdb_%(fname)s.la
libdb_%(fname)s_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_%(fname)s_la_SOURCES = db_%(fname)s.h
libdb_%(fname)s_la_SOURCES += db_%(fname)s.cc
"""

def main(argv):
  print "BE VERY CAREFUL -- you must look at the code."
  return 0
  classes = [('user_device', 'UserDevice'),
             ('device_sync', 'DeviceSync'),
             ('user_top_dir', 'UserTopDir'),
             ('email_key', 'EmailKey'),
             # ('top_dir_meta', 'TopDirMeta'),
             ('top_dir_relpath_lock', 'TopDirRelpathLock'),
             ('top_dir_snaps', 'TopDirSnaps'),
             ('top_dir_data', 'TopDirData'),
             ('top_dir_fptrs', 'TopDirFptrs')]
  for fname, klass in classes:
    # Create the .h and .cc files.
    with open('db_' + fname + '.h','w') as fh:
      fh.write(kHeaderBase % {'klass': klass})
    with open('db_' + fname + '.cc','w') as fh:
      fh.write(kImplBase % {'klass': klass,
                            'fname': fname})

    # Generate the automake contents.
    print kAutomakeBase % {'fname': fname}

if __name__=='__main__':
  main(sys.argv)
