#ifndef _LOCKBOX_FILE_UTIL_H
#define _LOCKBOX_FILE_UTIL_H

#include "base/files/file_path.h"
#include "base/platform_file.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>

using std::string;

namespace lockbox {

bool IsDirectory(const base::FilePath& fpath);

string GetHomeDirectory();

} // namespace lockbox

#endif  // _LOCKBOX_FILE_UTIL_H
