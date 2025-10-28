#include "panel.h"

#include "../appl/application.h"
#include "../window/gl_window.h"

#include <imgui.h>

#include <iostream>

namespace lviz {
namespace ui {

Panel::Panel(window::Window *parent)
    : parent_(parent), file_dialog_(), current_file_() {
  file_dialog_.SetTitle("Open script");
  file_dialog_.SetTypeFilters({".lua"});
}

Panel::~Panel() {}

void Panel::Render() {
  ImGui::Begin("Control panel");

  if (ImGui::Button("Open script")) {
    file_dialog_.Open();
  }

  if (ImGui::Button("Run script")) {
    auto gl_win = dynamic_cast<window::GLWindow *>(parent_);
    if (gl_win) {
      appl::State *state = gl_win->GetApp()->GetState();
      std::string error{};
      if (!state->DoFile(current_file_, error))
        std::cout << error << std::endl;
    }
  }

  ImGui::End();

  file_dialog_.Display();
  if (file_dialog_.HasSelected()) {
    current_file_ = file_dialog_.GetSelected().string();
    file_dialog_.ClearSelected();
  }
}

} // namespace ui
} // namespace lviz
