#ifndef _LVIZ_CANVAS_UTIL_H
#define _LVIZ_CANVAS_UTIL_H

#include <cmath>
#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

class Math {
public:
  static constexpr glm::f32 Pi() {
    return 3.1415926535897932;
  }

  static constexpr glm::f32 LinearDeflection() {
    return 0.01;
  }

  static constexpr glm::f32 AngularDeflection() {
    return Pi() / 36.0; // 5 degree
  }
};

} // namespace canvas
} // namespace lviz

#endif
