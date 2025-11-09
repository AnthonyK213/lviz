#include "application.h"

#include "../bind/bind.h"

#include <iostream>

namespace lviz {
namespace appl {

Application::Application()
    : window_(nullptr), manager_(nullptr), log_stream_(nullptr),
      state_(nullptr) {
  std::filesystem::path app_local = util::AppPath::AppLocalDataLocation();
  if (!app_local.empty()) {
    if (!std::filesystem::is_directory(app_local)) {
      if (!std::filesystem::create_directories(app_local)) {
        app_local.clear();
      }
    }
  }

  window_ = std::make_unique<window::GLWindow>(this);
  window_->Init(1024, 720, "lviz");

  state_ = std::make_unique<State>();
  state_->Init();

  manager_ = std::make_unique<ExtensionManager>(this);

  if (app_local.empty()) {
    std::cout << "AppLocalDataLocation was not found" << std::endl;
  } else {
    std::filesystem::path ext_dir = app_local / "extensions";
    if (std::filesystem::is_directory(ext_dir) ||
        std::filesystem::create_directory(ext_dir)) {
      manager_->Init(ext_dir);
      manager_->Load();
    }
  }

  bind::BindGP(state_->GetLuaState());
  bind::BindCanvas(state_->GetLuaState());
  bind::BindAppl(state_->GetLuaState(), manager_.get());
  bind::BindUI(state_->GetLuaState(), window_.get());
  bind::BindIO(state_->GetLuaState());

  log_stream_ = std::make_unique<LogStream>(std::cout, window_->GetLog());
}

Application::~Application() {
  state_ = nullptr;      // Destruct before window_.
  log_stream_ = nullptr; // Destruct before window_.
  manager_ = nullptr;
  window_ = nullptr;
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
