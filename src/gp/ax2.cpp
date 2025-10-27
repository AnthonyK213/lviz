#include "ax2.h"

namespace lviz {
namespace gp {

Ax2::Ax2(const Pnt &location, const Vec &direction)
    : axis_(location, direction), x_dir_(1.0, 0.0, 0.0) {
  y_dir_ = glm::cross(axis_.Direction(), x_dir_);
  if (glm::length(y_dir_) < 1e-6f) {
    x_dir_ = Vec(0.0, 1.0, 0.0);
    y_dir_ = glm::cross(axis_.Direction(), x_dir_);
  }
  y_dir_ = glm::normalize(y_dir_);
  x_dir_ = glm::normalize(glm::cross(y_dir_, axis_.Direction()));
}

Pnt Ax2::Evaluate(const glm::f32 x, const glm::f32 y, const glm::f32 z) const {
  return Location() + x * XDirection() + y * YDirection() + z * Direction();
}

} // namespace gp

} // namespace lviz
