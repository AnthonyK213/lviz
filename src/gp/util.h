#ifndef _LVIZ_GP_UTIL_H
#define _LVIZ_GP_UTIL_H

#include <glm/glm.hpp>

#include <cmath>
#include <limits>

namespace lviz {
namespace gp {

class Math {
public:
  static constexpr glm::f32 Zero() {
    return 1.0e-8f;
  }

  static constexpr glm::f32 UnsetFloat() {
    return std::numeric_limits<glm::f32>::quiet_NaN();
  }

  static bool IsUnsetFloat(glm::f32 value) {
    return std::isnan(value);
  }

  static constexpr glm::f32 Infinite() {
    return 1.0e20f;
  }

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
    return 1.0e-2f;
  }

  static constexpr glm::f32 AngularDeflection() {
    return ToRad(6.0f);
  }
};

} // namespace gp
} // namespace lviz

#endif
