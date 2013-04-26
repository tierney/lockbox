namespace cpp lockbox

struct UserProfile {
  1: i32 uid,
  2: string name,
  3: string blurb
}

struct UserAuth {
  1: string email,
  2: string password,
}

// Client maps the return value to the top directory name.
struct Device {
  1: i64 user_id,
}

service Registration {
  // Returns the UID.
  i64 RegisterUser(1:UserAuth user),

  // Returns the Device ID.
  i64 RegisterDevice(1:UserAuth user, 2:Device device),

  // Returns the top directory's GUID.
  i64 RegisterTopDir(1:UserAuth user),
}

service UserStorage {
  void store(1: UserProfile user),
  UserProfile retrieve(1: i32 uid)
}
