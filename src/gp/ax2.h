#ifndef _LVIZ_GP_AX2_H
#define _LVIZ_GP_AX2_H

#include "ax1.h"

namespace lviz {
namespace gp {

class Ax2 {
public:
  Ax2(const Pnt &location, const Vec &direction);

  const Ax1 &Axis() const {
    return axis_;
  }

  const Pnt &Location() const {
    return axis_.Location();
  }

  const Vec &Direction() const {
    return axis_.Direction();
  }

  const Vec &XDirection() const {
    return x_dir_;
  }

  const Vec &YDirection() const {
    return y_dir_;
  }

  Pnt Evaluate(const glm::f32 x, const glm::f32 y, const glm::f32 z) const;

private:
  Ax1 axis_;
  Vec x_dir_;
  Vec y_dir_;
};

} // namespace gp
} // namespace lviz

#endif
