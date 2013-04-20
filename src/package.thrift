namespace cpp lockbox;

enum PackageType {
  SNAPSHOT,
  DELTA,
}

struct Package {
  1: required string path,
  2: required string hash,
  3: optional PackageType type,
  4: optional string contents,
}
