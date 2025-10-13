#include "application.h"

namespace lviz {
namespace appl {

static void bindView3d(lua_State *lua_state, ui::View3d *view3d) {
  /* TODO: Register view3d as lightuserdata */

  /* TODO: Bind methods of View3d */
}

Application::Application(const std::string &app_name) {
  window_ = std::make_unique<window::GLWindow>();
  window_->Init(1024, 720, app_name);

  state_ = std::make_unique<State>();
  if (state_->Init()) {
    bindView3d(state_->GetLuaState(), window_->GetView3d());
  }
}

void Application::Run() {
  while (window_->IsRunning()) {
    window_->Render();
  }
}

} // namespace appl
} // namespace lviz
