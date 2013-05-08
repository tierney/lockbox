#pragma once

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"
#include "leveldb/db.h"
#include "lockbox_types.h"
#include "counter.h"

using std::map;
using std::string;
using std::vector;

namespace lockbox {

class DBManager {
 public:
  struct Options {
    Options() : type(0), name("") {}

    Options(int type, const string& name) : type(type), name(name) {}

    // Enumed value.
    int type;

    // Used by TopDir databases in order to locate the database.
    string name;
  };

  explicit DBManager(const string& db_location_base,
                     const map<int, const char*> values_to_names);

  virtual ~DBManager();

  virtual bool Get(const Options& options, const string& key, string* value);

  virtual bool GetList(const Options& options, const string& key_prefix,
                       vector<string>* values);

  virtual bool Put(const Options& options, const string& key, const string& value);

  virtual bool Append(const Options& options,
                      const string& key,
                      const string& new_value);

  virtual bool Delete(const Options& options, const string& key);

  virtual bool First(const Options& options, string* key, string* value);

  virtual bool NewTopDir(const Options& options);

  virtual bool Track(const Options& options);

  virtual uint64_t MaxID(const Options& options);

  // Creates pathhs of the name /a/path/to/the/dest/THIS_IS_A_TYPE/OPTIONS_NAME.
  virtual string GenPath(const string& base, const Options& options);

  // Creates keys of the name THIS_IS_A_TYPE and THIS_IS_A_TYPEOPTIONS_NAME.
  virtual string GenKey(const Options& options);

  virtual leveldb::DB* db(const Options& options);

 protected:
  string db_location_base_;
  map<string, leveldb::DB*> db_map_;
  map<int, const char*> values_to_names_;

};

} // namespace lockbox
