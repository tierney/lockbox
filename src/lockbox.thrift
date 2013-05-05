namespace cpp lockbox

# Basic authentication.
struct UserAuth {
  1: required string email,
  2: required string password,
}

typedef i64 DeviceID
typedef i64 UserID
typedef i64 TopDirID

# Packages uploaded for storage and sharing on Lockbox.
enum PackageType {
  SNAPSHOT,
  DELTA,
}

struct LocalPackage {
  1: required string base_abs_path,
  2: required string base_rel_path,
  3: PackageType type,
  4: string contents,
}

struct HybridCrypto {
  1: required string data,
  2: map<string, string> user_enc_session,
}

struct RemotePackage {
  1: required string top_dir,
  2: required string rel_path_id,
  3: required PackageType type,
  4: required HybridCrypto path,
  5: required HybridCrypto payload,
}

struct DownloadRequest {
  1: required UserAuth auth,
  2: required string top_dir,
  3: required string pkg_name,
}

struct RegisterRelativePathRequest {
  1: required UserAuth user,
  2: required string top_dir,
}

struct PathLockRequest {
  1: required UserAuth user,
  2: required string top_dir,
  3: string rel_path,
  4: i32 seconds_requested,
}

struct PathLockResponse {
  1: required bool acquired,
  2: required list<string> users,
}

# When a user requests an update list for files to fetch, this is the list that
# the user can use to fetch requests for new downloads.
struct Updates {
  1: required string device,
  2: required string user,
  3: list<HybridCrypto> updates,
}

# This should best match the C++ openssl expectation that we export to a
# vector<uint8>.
struct PublicKey {
  1: required string key,
}

# Hash Chain Digests. Follows the methodology outlined by Jinyuan Li.
#
struct HashChainDigestHistory {
  1: required list<string> history,
}

struct HashChainDigestEntry {
  1: required i64 view,
  2: required i64 seq_no,
  3: required string digest,
  4: required string signature,
}

# TODO(tierney): These should be tied to the TDN and relative paths too...
struct VersionInfo {
  1: map<i32, HashChainDigestEntry> vector,
  2: HashChainDigestHistory history
}

# Database names.
enum ServerDB {
  UNKNOWN = 0

  EMAIL_USER,
  USER_DEVICE,
  DEVICE_SYNC,
  EMAIL_KEY,
  USER_TOP_DIR, # Maps user to directories owned.

  TOP_DIR_PLACEHOLDER,

  TOP_DIR_META, # Who's sharing the data "EDITORS"
  TOP_DIR_RELPATH, # RELPATH_ID -> first hash for the relpath.
  TOP_DIR_RELPATH_LOCK, # RELPATH_ID -> lock
  TOP_DIR_SNAPSHOTS, # RELPATH_ID -> list of all snapshots, in order.
  TOP_DIR_DATA, # HASH -> bytes...
  TOP_DIR_FPTRS, # HASH_i -> HASH_(i+1)
}

enum ClientDB {
  UNKNOWN = 0,

  TOP_DIR_LOCATION,
  EMAIL_KEY,
  CLIENT_DATA, #
  UNFILTERED_QUEUE,

  TOP_DIR_PLACEHOLDER,

  RELPATH_ID_LOCATION,
  RELPATHS_HASH,
  RELPATHS_TIME,
  UPDATE_QUEUE_SERVER,
  UPDATE_QUEUE_CLIENT,
  FILE_CHANGES,
}

# Unifying Service
#
service LockboxService {
  # Returns the UID.
  UserID RegisterUser(1:UserAuth user),

  # Returns the Device ID.
  DeviceID RegisterDevice(1:UserAuth user),

  # Returns the top directory's GUID.
  TopDirID RegisterTopDir(1:UserAuth user),

  # Attach a public key to a user.
  bool AssociateKey(1:UserAuth user, 2:PublicKey pub),

  # Get relative path ID for the TDN.
  string RegisterRelativePath(1:RegisterRelativePathRequest req),

  # Grab lock on rel path for the TDN.
  PathLockResponse AcquireLockRelPath(1:PathLockRequest lock),

  void ReleaseLockRelPath(1:PathLockRequest lock),

  i64 UploadPackage(1:RemotePackage pkg),

  LocalPackage DownloadPackage(1:DownloadRequest req),

  Updates PollForUpdates(1:UserAuth auth, 2:DeviceID device),

  # Hash chain service API.
  void Send(1:UserAuth sender, 2:string receiver_email, 3:VersionInfo vinfo),

  VersionInfo GetLatestVersion(1:UserAuth requestor, 2:string receiver_email),
}
