#ifndef _LVIZ_UTIL_APP_PATH_H
#define _LVIZ_UTIL_APP_PATH_H

#include <filesystem>

namespace lviz {
namespace util {

class AppPath {
public:
  static std::filesystem::path ApplicationDirPath();

  static std::filesystem::path AppLocalDataLocation();

  static std::filesystem::path AppResourcesDir();
};

} // namespace util
} // namespace lviz

#endif
