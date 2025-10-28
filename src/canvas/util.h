#ifndef _LVIZ_CANVAS_UTIL_H
#define _LVIZ_CANVAS_UTIL_H

#include <cmath>
#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

class Math {
public:
  static constexpr glm::f32 Pi() {
    return 3.14159265358979323846f;
  }

  static constexpr glm::f32 LinearDeflection() {
    return 1e-2f;
  }

  static constexpr glm::f32 AngularDeflection() {
    return Pi() / 30.0; // 6 degree
  }
};

} // namespace canvas
} // namespace lviz

#endif
