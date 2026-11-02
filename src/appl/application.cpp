#include "application.h"

#include "../bind/bind.h"
#include "../util/app_path.h"

#include <uv.h>

#include <iostream>

namespace lviz {
int g_frames_to_render = 0;
void g_reset_frames_to_render() {
  g_frames_to_render = 3;
}
} // namespace lviz

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

  std::filesystem::path rt_dir = util::AppPath::AppResourcesDir();
  if (!rt_dir.empty()) {
    if (std::filesystem::is_directory(rt_dir)) {
      state_->PathAppend((rt_dir / "runtime" / "lua").string() + "/?.lua");
    }
  }

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

  bind::BindUV(state_->GetLuaState());
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
  g_reset_frames_to_render();
  while (window_->IsRunning()) {
    window_->WaitEvents();
    uv_run(uv_default_loop(), UV_RUN_NOWAIT);
    if (g_frames_to_render <= 0)
      continue;
    g_frames_to_render--;
    window_->Render();
    window_->HandleInput();
  }
}

} // namespace appl
} // namespace lviz
