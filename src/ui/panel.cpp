#include "panel.h"

#include <imgui.h>

#include <iostream>

namespace lviz {
namespace ui {

Panel::Panel() : file_dialog_(), current_file_() {
  file_dialog_.SetTitle("Open script");
  file_dialog_.SetFileFilters({".lua"});
}

Panel::~Panel() {}

void Panel::Render() {
  ImGui::Begin("Control panel");

  if (ImGui::Button("Open script")) {
    file_dialog_.Open();
  }

  if (ImGui::Button("Run script")) {
    /* TODO: Run the script */
    std::cout << current_file_ << std::endl;
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
