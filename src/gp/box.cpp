#include "box.h"
#include "../util/math.h"

namespace lviz {
namespace gp {

Box::Box() : min_(1.0, 0.0, 0.0), max_(-1.0, 0.0, 0.0) {}

Box::Box(const Pnt &min_pnt, const Pnt &max_pnt)
    : min_(min_pnt), max_(max_pnt) {}

bool Box::IsVoid() const {
  return min_.x > max_.x || min_.y > max_.y || min_.z > max_.z;
}

bool Box::IsPoint() const {
  return min_ == max_;
}

std::vector<Pnt> Box::Corners() const {
  if (IsVoid())
    return {};

  return {
      Pnt(min_.x, min_.y, min_.z), Pnt(max_.x, min_.y, min_.z),
      Pnt(max_.x, max_.y, min_.z), Pnt(min_.x, max_.y, min_.z),
      Pnt(min_.x, min_.y, max_.z), Pnt(max_.x, min_.y, max_.z),
      Pnt(max_.x, max_.y, max_.z), Pnt(min_.x, max_.y, max_.z),
  };
}

void Box::Scale(glm::f32 scale) {
  min_ *= scale;
  max_ *= scale;
}

void Box::Enlarge(glm::f32 value) {
  min_ -= value;
  max_ += value;
}

void Box::Unite(const Box &other) {
  if (other.IsVoid())
    return;

  update(other.min_.x, other.min_.y, other.min_.z, other.max_.x, other.max_.y,
         other.max_.z);
}

void Box::Unite(const Pnt &point) {
  update(point.x, point.y, point.z);
}

void Box::update(const glm::f32 x_min, const glm::f32 y_min,
                 const glm::f32 z_min, const glm::f32 x_max,
                 const glm::f32 y_max, const glm::f32 z_max) {
  if (IsVoid()) {
    min_.x = x_min;
    min_.y = y_min;
    min_.z = z_min;
    max_.x = x_max;
    max_.y = y_max;
    max_.z = z_max;
  } else {
    if (x_min < min_.x)
      min_.x = x_min;
    if (y_min < min_.y)
      min_.y = y_min;
    if (z_min < min_.z)
      min_.z = z_min;
    if (x_max > max_.x)
      max_.x = x_max;
    if (y_max > max_.y)
      max_.y = y_max;
    if (z_max > max_.z)
      max_.z = z_max;
  }
}

void Box::update(const glm::f32 x, const glm::f32 y, const glm::f32 z) {
  if (IsVoid()) {
    min_.x = max_.x = x;
    min_.y = max_.y = y;
    min_.z = max_.z = z;
  } else {
    if (x < min_.x)
      min_.x = x;
    else if (x > max_.x)
      max_.x = x;

    if (y < min_.y)
      min_.y = y;
    else if (y > max_.y)
      max_.y = y;

    if (z < min_.z)
      min_.z = z;
    else if (z > max_.z)
      max_.z = z;
  }
}

} // namespace gp
} // namespace lviz
