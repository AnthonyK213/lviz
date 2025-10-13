#ifndef _LVIZ_UI_VIEW3D_H
#define _LVIZ_UI_VIEW3D_H

#include <glm/glm.hpp>

namespace lviz {
namespace ui {

class View3d {
public:
  View3d();

  ~View3d();

  void Render();

  bool DrawPoint(const glm::vec3 &point);

  bool DrawLineSegment(const glm::vec3 &point1, const glm::vec3 &point2);

  bool DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                    const glm::vec3 &point3);

private:
};

} // namespace ui
} // namespace lviz

#endif
