namespace cpp lockbox;

enum PackageType {
  SNAPSHOT,
  DELTA,
}

struct LocalPackage {
  1: required string base_abs_path,
  2: required string base_rel_path,
  3: optional PackageType type,
  4: optional string contents,
}

struct RemotePackage {
  1: required string base_abs_path,
  2: required HybridCrypto path,
  3: required HybridCrypto data,
}

struct HybridCrypto {
  1: required string data,
  2: optional map<string, string> user_enc_session,
}

struct PathLock {
  1: required string base_abs_path,
  2: required string user,
  3: required i32 seconds_requested,
}

# When a user requests an update list for files to fetch, this is the list that
# the user can use to fetch requests for new downloads.
struct Updates {
  1: required string device,
  2: required string user,
  3: optional list<HybridCrypto> updates,
}

service Package Exchange {
  bool lock(1:PathLock lock),
  bool upload(1:LocalPackage pkg),
  bool download(),
  bool poll(),
}