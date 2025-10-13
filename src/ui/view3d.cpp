#include "view3d.h"

#include <imgui.h>

namespace lviz {
namespace ui {

View3d::View3d() {}

View3d::~View3d() {}

void View3d::Render() {
  ImGui::Begin("View3d");

  ImGui::End();
}

} // namespace ui
} // namespace lviz
