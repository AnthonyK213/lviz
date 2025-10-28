#include "glm.h"
#include "util.h"

namespace lviz {
namespace gp {

const glm::vec3 &UnsetXYZ() {
  static glm::vec3 unset{Math::UnsetFloat()};
  return unset;
}

bool IsUnsetXYZ(const glm::vec3 &xyz) {
  return glm::any(glm::isnan(xyz));
}

} // namespace gp

} // namespace lviz
