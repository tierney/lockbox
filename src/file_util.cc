#include "file_util.h"

#include "base/logging.h"

namespace lockbox {

bool IsDirectory(const base::FilePath& fpath, bool* is_directory) {
  CHECK(fpath.IsAbsolute());
  bool created = false;
  base::PlatformFileError error = base::PLATFORM_FILE_ERROR_FAILED;
  base::PlatformFile pf(
      CreatePlatformFile(fpath,
                         base::PLATFORM_FILE_OPEN | base::PLATFORM_FILE_READ,
                         &created,
                         &error));
  if (base::PLATFORM_FILE_OK != error) {
    LOG(ERROR) << "PlatformFile error " << error;
    return false;
  }

  base::PlatformFileInfo info;
  if (!base::GetPlatformFileInfo(pf, &info)) {
    LOG(ERROR) << " info problem";
    return false;
  }
  *is_directory = info.is_directory;
  return true;
}

string GetHomeDirectory() {
  struct passwd *pw = getpwuid(getuid());
  return pw->pw_dir;
}

}
