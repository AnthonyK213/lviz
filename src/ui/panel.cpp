#include "panel.h"

#include <imgui.h>

namespace lviz {
namespace ui {

Panel::Panel() {}

Panel::~Panel() {}

void Panel::Render() {
  ImGui::Begin("Control panel");

  if (ImGui::Button("Open script")) {
    /* TODO: Open the file dialog */
  }

  ImGui::End();
}

} // namespace ui
} // namespace lviz
