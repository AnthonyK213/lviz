#ifndef _LVIZ_GP_XYZ_H
#define _LVIZ_GP_XYZ_H

#include <glm/glm.hpp>

namespace lviz {
namespace gp {

using Pnt = glm::vec3;
using Vec = glm::vec3;

const glm::vec3 &UnsetXYZ();

bool IsUnsetXYZ(const glm::vec3 &xyz);

glm::f32 PntDistance(const Pnt &a, const Pnt &b);

glm::f32 PntDistance2(const Pnt &a, const Pnt &b);

glm::f32 VecMagnitude(const Vec &a);

glm::f32 VecDot(const Vec &a, const Vec &b);

Vec VecCrossed(const Vec &a, const Vec &b);

glm::f32 VecAngle(const Vec &a, const Vec &b);

glm::f32 VecAngleWithRef(const Vec &a, const Vec &b, const Vec &ref);

} // namespace gp
} // namespace lviz

#endif
