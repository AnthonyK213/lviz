#ifndef _LVIZ_GP_BOX_H
#define _LVIZ_GP_BOX_H

#include "xyz.h"

#include <vector>

namespace lviz {
namespace gp {

class Box {
public:
  Box();

  Box(const Pnt &min_pnt, const Pnt &max_pnt);

  bool IsVoid() const;

  bool IsPoint() const;

  const Pnt &Min() const {
    return min_;
  }

  const Pnt &Max() const {
    return max_;
  }

  Pnt Center() const {
    return 0.5f * (min_ + max_);
  }

  std::vector<Pnt> Corners() const;

  void Enlarge(glm::f32 value);

  void Unite(const Box &other);

  void Unite(const Pnt &point);

private:
  void update(const glm::f32 x_min, const glm::f32 y_min, const glm::f32 z_min,
              const glm::f32 x_max, const glm::f32 y_max, const glm::f32 z_max);

  void update(const glm::f32 x, const glm::f32 y, const glm::f32 z);

private:
  Pnt min_;
  Pnt max_;
};

} // namespace gp
} // namespace lviz

#endif
