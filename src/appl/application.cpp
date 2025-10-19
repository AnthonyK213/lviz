#if defined(_WIN32)
#include <ShlObj.h>
#include <Windows.h>
#elif defined(__linux__)
#elif defined(__APPLE__)
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "application.h"

#include "../bind/bind.h"

#include <iostream>
#include <optional>

namespace lviz {
namespace appl {

static std::optional<std::filesystem::path> getAppLocalDataLocation() {
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
#elif defined(__linux__)
  return {};
#elif defined(__APPLE__)
  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);
  if (pw) {
    return std::filesystem::path(pw->pw_dir) / ".local" / "share" / "lviz";
  } else {
    return {};
  }
#else
  return {};
#endif
}

Application::Application(const std::string &app_name)
    : window_(nullptr), manager_(nullptr), state_(nullptr) {
  std::optional<std::filesystem::path> app_local = getAppLocalDataLocation();
  if (app_local) {
    if (!std::filesystem::is_directory(app_local.value())) {
      if (!std::filesystem::create_directories(app_local.value())) {
        app_local.reset();
      }
    }
  }

  window_ = std::make_unique<window::GLWindow>(this);
  window_->Init(1024, 720, app_name);

  state_ = std::make_unique<State>();
  state_->Init();

  manager_ = std::make_unique<ExtensionManager>(this);

  if (!app_local) {
    std::cout << "AppLocalDataLocation was not found" << std::endl;
  } else {
    std::filesystem::path ext_dir = app_local.value() / "extensions";
    if (std::filesystem::is_directory(ext_dir) ||
        std::filesystem::create_directory(ext_dir)) {
      manager_->Init(ext_dir);
      manager_->Load();
    }
  }

  bind::BindGLM(state_->GetLuaState());
  bind::BindView3d(state_->GetLuaState(), window_->GetView3d());
  bind::BindExtension(state_->GetLuaState());
  bind::BindExtensionManager(state_->GetLuaState(), manager_.get());
}

void Application::Run() {
  while (window_->IsRunning()) {
    window_->WaitEvents();
    window_->Render();
    window_->HandleInput();
  }
}

} // namespace appl
} // namespace lviz
