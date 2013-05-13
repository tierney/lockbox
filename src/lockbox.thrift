namespace cpp lockbox

typedef string DeviceID
typedef string UserID
typedef string TopDirID

# Packages uploaded for storage and sharing on Lockbox.
enum PackageType {
  SNAPSHOT,
  DELTA,
}

# Basic authentication.
struct UserAuth {
  1: required string email,
  2: required string password,
  3: DeviceID device,
}

struct HybridCrypto {
  1: required string data,
  2: map<string, string> user_enc_session,
  3: string data_sha1,
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
struct Update {
  1: i64 timestamp,
  2: string top_dir_id,
  3: string rel_path_id,
  4: string hash,
}

# TODO: Possible switch to using the struct Update.
struct UpdateMap {
  1: map<string, string> updates,
}

struct UpdateList {
  1: list<string> updates,
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
  USER_DEVICE, # Email to device id
  DEVICE_SYNC,
  EMAIL_KEY,
  USER_TOP_DIR, # Maps user to directories managed.
  UPDATE_ACTION_QUEUE, # Holds (TS, TDN, RPI, hash) value for updates.
  UPDATE_ACTION_LOG, # Holds (TS, TDN, RPI, hash) for creation -> completion.

  TOP_DIR_PLACEHOLDER,

  TOP_DIR_META, # Who's sharing the data "EDITORS"
  TOP_DIR_RELPATH, # RELPATH_ID -> latest hash for the relpath.
  TOP_DIR_RELPATH_LOCK, # RELPATH_ID -> lock
  TOP_DIR_SNAPSHOTS, # RELPATH_ID -> list of all snapshots, in order.
  TOP_DIR_DATA, # HASH -> bytes...
  TOP_DIR_FPTRS, # HASH_i -> HASH_(i-1)
}

enum ClientDB {
  UNKNOWN = 0,

  TOP_DIR_LOCATION,
  LOCATION_TOP_DIR,
  EMAIL_KEY,
  CLIENT_DATA, #
  UNFILTERED_QUEUE,

  TOP_DIR_PLACEHOLDER, # All TOP_DIR-specific DBs follow.

  RELPATH_ID_LOCATION, # path to file system path
  LOCATION_RELPATH_ID, # path to file system path

  RELPATH_LOCK,

  # Points to the hash in data containing the latest entry. May contain delta or
  # snapshot.
  RELPATHS_HEAD_HASH,

  # Contains the whole snapshot file of the previous version (that pointed to by
  # RELPATHS_HEAD)
  RELPATHS_HEAD_FILE,

  # Contains the whole snapshot file's (RELPATHS_HEAD_FILE) SHA1 hash.
  RELPATHS_HEAD_FILE_HASH,

  UPDATE_QUEUE_SERVER,
  UPDATE_QUEUE_CLIENT,
  FILE_CHANGES,
  DATA,
  FPTRS,
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

  # Share directory.
  bool ShareTopDir(1:UserAuth user, 2:string email, 3:TopDirID top_dir_id),

  list<TopDirID> GetTopDirs(1:UserAuth user);

  # Attach a public key to a user.
  bool AssociateKey(1:UserAuth user, 2:PublicKey pub),

  PublicKey GetKeyFromEmail(1:string email),

  # Get relative path ID for the TDN.
  string RegisterRelativePath(1:RegisterRelativePathRequest req),

  # Grab lock on rel path for the TDN.
  PathLockResponse AcquireLockRelPath(1:PathLockRequest lock),

  void ReleaseLockRelPath(1:PathLockRequest lock),

  i64 UploadPackage(1:UserAuth user, 2:RemotePackage pkg),

  RemotePackage DownloadPackage(1:DownloadRequest req),

  UpdateMap PollForUpdates(1:UserAuth auth, 2:DeviceID device),

  # Update the UPDATE_ACTION_LOG and then set delete the values from the
  # DEVICE_SYNC.
  void PersistedUpdates(1:UserAuth auth, 2:DeviceID device,
                        3:UpdateList updates),

  # Hash chain service API.
  void Send(1:UserAuth sender, 2:string receiver_email, 3:VersionInfo vinfo),

  VersionInfo GetLatestVersion(1:UserAuth requestor, 2:string receiver_email),
}
