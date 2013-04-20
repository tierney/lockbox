namespace cpp lockbox;

struct HCDHistory {
  1: required list<string> history,
}

struct Entry {
  1: required i64 view,
  2: required i64 seq_no,
  3: required string hcd,
  4: required string signature,
}

struct Version {
  1: optional map<i32, Entry> vector,
  2: optional HCDHistory history
}

service VersionExchange {
  void Send(1: Version version),
  Version GetLatestVersion(),
}