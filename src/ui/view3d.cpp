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

bool View3d::DrawPoint(const glm::vec3 &point) {
  return true;
}

bool View3d::DrawLineSegment(const glm::vec3 &point1, const glm::vec3 &point2) {
  return true;
}

bool View3d::DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                          const glm::vec3 &point3) {
  return true;
}

} // namespace ui
} // namespace lviz
