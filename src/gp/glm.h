#ifndef _LVIZ_GP_GLM_H
#define _LVIZ_GP_GLM_H

#include <glm/glm.hpp>

namespace lviz {
namespace gp {

using Pnt = glm::vec3;
using Vec = glm::vec3;

const glm::vec3 &UnsetXYZ();

bool IsUnsetXYZ(const glm::vec3 &xyz);

} // namespace gp
} // namespace lviz

#endif
