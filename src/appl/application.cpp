#include "application.h"

namespace lviz {
namespace appl {

Application::Application(const std::string &app_name) {
  window_ = std::make_unique<window::GLWindow>();
  window_->Init(1024, 720, app_name);
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
