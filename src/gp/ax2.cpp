#include "ax2.h"
#include "../util/math.h"

namespace lviz {
namespace gp {

Ax2::Ax2() : axis_(), x_dir_(1.0, 0.0, 0.0), y_dir_(0.0, 1.0, 0.0) {}

Ax2::Ax2(const Pnt &location, const Vec &direction)
    : axis_(location, direction), x_dir_(1.0, 0.0, 0.0) {
  y_dir_ = glm::cross(axis_.Direction(), x_dir_);
  if (glm::length(y_dir_) < util::Math::Zero()) {
    x_dir_ = Vec(0.0, 1.0, 0.0);
    y_dir_ = glm::cross(axis_.Direction(), x_dir_);
  }
  y_dir_ = glm::normalize(y_dir_);
  x_dir_ = glm::normalize(glm::cross(y_dir_, axis_.Direction()));
}

Ax2::Ax2(const Pnt &location, const Vec &x_direction, const Vec &y_direction) {
  Vec direction = glm::cross(x_direction, y_direction);
  axis_ = Ax1(location, direction);
  x_dir_ = glm::normalize(x_direction);
  y_dir_ = glm::normalize(glm::cross(axis_.Direction(), x_dir_));
}

Pnt Ax2::ToWorld(const gp::Pnt &local_coord) const {
  return Location() + local_coord.x * XDirection() +
         local_coord.y * YDirection() + local_coord.z * Direction();
}

Pnt Ax2::ToLocal(const gp::Pnt &world_coord) const {
  gp::Vec v = world_coord - Location();
  return gp::Pnt{glm::dot(v, XDirection()), glm::dot(v, YDirection()),
                 glm::dot(v, Direction())};
}

} // namespace gp

} // namespace lviz
