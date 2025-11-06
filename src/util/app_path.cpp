#if defined(_WIN32)
#include <ShlObj.h>
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "app_path.h"

namespace lviz {
namespace util {

std::filesystem::path AppPath::ApplicationDirPath() {
#if defined(_WIN32)
  char path[MAX_PATH];
  GetModuleFileNameA(nullptr, path, MAX_PATH);
  std::filesystem::path sPath{path};
  return sPath.parent_path();
#elif defined(__linux__)
  return {};
#elif defined(__APPLE__)
  return {};
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

} // namespace util
} // namespace lviz
