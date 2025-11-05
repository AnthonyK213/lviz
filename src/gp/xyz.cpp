#include "xyz.h"
#include "../util/math.h"

namespace lviz {
namespace gp {

const glm::vec3 &UnsetXYZ() {
  static glm::vec3 unset{util::Math::UnsetFloat()};
  return unset;
}

bool IsUnsetXYZ(const glm::vec3 &xyz) {
  return glm::any(glm::isnan(xyz));
}

glm::f32 PntDistance(const Pnt &a, const Pnt &b) {
  return glm::distance(a, b);
}

glm::f32 PntDistance2(const Pnt &a, const Pnt &b) {
  glm::vec3 v = a - b;
  return glm::dot(v, v);
}

glm::f32 VecMagnitude(const Vec &a) {
  return glm::length(a);
}

glm::f32 VecDot(const Vec &a, const Vec &b) {
  return glm::dot(a, b);
}

Vec VecCrossed(const Vec &a, const Vec &b) {
  return glm::cross(a, b);
}

glm::f32 VecAngle(const Vec &a, const Vec &b) {
  glm::f32 a_len = glm::length(a);
  glm::f32 b_len = glm::length(b);
  if (a_len < util::Math::Zero() || b_len < util::Math::Zero())
    return util::Math::UnsetFloat();
  glm::f32 cos_theta = glm::dot(a, b) / (a_len * b_len);
  return std::acos(cos_theta);
}

glm::f32 VecAngleWithRef(const Vec &a, const Vec &b, const Vec &ref) {
  glm::f32 angle = VecAngle(a, b);
  Vec normal = glm::cross(a, b);
  return (glm::dot(normal, ref) > 0.0f) ? angle : -angle;
}

} // namespace gp
} // namespace lviz
