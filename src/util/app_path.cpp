#if defined(_WIN32)
#include <ShlObj.h>
#include <Windows.h>
#elif defined(__linux__)
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "app_path.h"

#include <vector>

namespace lviz {
namespace util {

std::filesystem::path AppPath::ApplicationDirPath() {
#if defined(_WIN32)
  char pathBuf[MAX_PATH];
  DWORD pathLen = GetModuleFileNameA(nullptr, pathBuf, MAX_PATH);
  if (pathLen > 0 && pathLen < MAX_PATH) {
    std::filesystem::path appPath{pathBuf};
    return appPath.parent_path();
  } else {
    return {};
  }
#elif defined(__linux__)
  return {};
#elif defined(__APPLE__)
  uint32_t bufsize = 0;
  _NSGetExecutablePath(nullptr, &bufsize);
  std::vector<char> pathBuf(bufsize);
  if (_NSGetExecutablePath(pathBuf.data(), &bufsize) == 0) {
    std::filesystem::path appPath{pathBuf.data()};
    return appPath.parent_path();
  } else {
    return {};
  }
#else
  return {};
#endif
}

std::filesystem::path AppPath::AppLocalDataLocation() {
#if defined(_WIN32)
  PWSTR path = nullptr;
  HRESULT result =
      SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path);
  if (SUCCEEDED(result)) {
    int buffer_size =
        WideCharToMultiByte(CP_ACP, 0, path, -1, nullptr, 0, nullptr, nullptr);
    std::string local_app_data_path;
    local_app_data_path.resize(buffer_size - 1);
    WideCharToMultiByte(CP_ACP, 0, path, -1, &local_app_data_path[0],
                        buffer_size, nullptr, nullptr);
    CoTaskMemFree(path);
    return std::filesystem::path(local_app_data_path) / "lviz";
  } else {
    return {};
  }
#elif defined(__linux__) || defined(__APPLE__)
  const char *home_dir = std::getenv("HOME");
  if (!home_dir) {
    home_dir = getpwuid(getuid())->pw_dir;
  }
  if (home_dir) {
    return std::filesystem::path(home_dir) / ".local" / "share" / "lviz";
  } else {
    return {};
  }
#else
  return {};
#endif
}

std::filesystem::path AppPath::AppResourcesDir() {
  std::filesystem::path appDir = ApplicationDirPath();
#if defined(__APPLE__)
  if (appDir.empty() || !appDir.has_parent_path())
    return {};
  return appDir.parent_path() / "Resources";
#else
  return appDir;
#endif
}

} // namespace util
} // namespace lviz
