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

  static constexpr glm::f32 Tau() {
    return 2.0f * Pi();
  }

  static constexpr glm::f32 HalfPi() {
    return 0.5f * Pi();
  }

  static constexpr glm::f32 ToRad(glm::f32 deg) {
    return deg * Pi() / 180.0f;
  }

  static constexpr glm::f32 ToDeg(glm::f32 rad) {
    return rad * 180.0f / Pi();
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
