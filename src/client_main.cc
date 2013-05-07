#include <string>
#include <vector>

#include "gflags/gflags.h"

#include "base/basictypes.h"
#include "base/file_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "client.h"

DEFINE_string(host, "", "Host to connect to for service.");
DEFINE_int32(port, 8888, "Port to connect to for host.");

DEFINE_string(email, "", "User's email address.");
DEFINE_string(password, "", "User's password");

DEFINE_string(config_path, "", "Absolute path to the config directory.");

DEFINE_bool(register_user, false, "Register new user.");
DEFINE_string(register_top_dir, "",
                "Absolute path to new directory (requires restart).");
DEFINE_string(unregister_top_dir, "",
                "Absolute path to new directory (requires restart).");

DEFINE_bool(daemon, true, "Run the app as daemon monitoring process.");

DEFINE_string(share, "", "Comma-separated value: DIRECTORY,EMAIL");
DEFINE_string(unshare, "", "Comma-separated value: DIRECTORY,EMAIL");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);

  lockbox::Client::ConnInfo conn_info(FLAGS_host, FLAGS_port);

  lockbox::DBManagerClient client_db(FLAGS_config_path);

  lockbox::UserAuth user_auth;
  user_auth.email = FLAGS_email;
  user_auth.password = FLAGS_password;

  lockbox::Client client(conn_info, &user_auth, &client_db);

  if (FLAGS_register_user) {
    client.RegisterUser();
  }

  if (!FLAGS_register_top_dir.empty()) {
    client.RegisterTopDir();
  }

  if (!FLAGS_share.empty()) {
    client.Share();
  }

  if (FLAGS_daemon) {
    client.Start();
  }

  return 0;
}
