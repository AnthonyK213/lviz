#ifndef _LVIZ_GP_AX1_H
#define _LVIZ_GP_AX1_H

#include "glm.h"

namespace lviz {
namespace gp {

class Ax1 {
public:
  /**
   * @brief World Z.
   *
   */
  Ax1();

  Ax1(const Pnt &location, const Vec &direction);

  const Pnt &Location() const {
    return loc_;
  }

  const Vec &Direction() const {
    return dir_;
  }

private:
  Pnt loc_;
  Vec dir_;
};

} // namespace gp
} // namespace lviz

#endif
