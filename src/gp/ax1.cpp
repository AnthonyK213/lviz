#include "ax1.h"

namespace lviz {
namespace gp {

Ax1::Ax1(const Pnt &location, const Vec &direction) : loc_(location), dir_() {
  dir_ = glm::normalize(direction);
}

} // namespace gp
} // namespace lviz
