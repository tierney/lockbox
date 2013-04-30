#pragma once
#include "base/files/file_path.h"
#include "base/platform_file.h"
namespace lockbox {

bool IsDirectory(const base::FilePath& fpath) {
  CHECK(fpath.IsAbsolute());
  bool created = false;
  base::PlatformFileError error = base::PLATFORM_FILE_ERROR_FAILED;
  base::PlatformFile pf(
      CreatePlatformFile(fpath,
                         base::PLATFORM_FILE_OPEN | base::PLATFORM_FILE_READ,
                         &created,
                         &error));
  CHECK(base::PLATFORM_FILE_OK == error) << "PlatformFile error " << error;
  base::PlatformFileInfo info;
  CHECK(base::GetPlatformFileInfo(pf, &info)) << " info problem";
  return info.is_directory;
}


} // namespace lockbox
