#ifndef _LVIZ_CANVAS_CIRCLE_H
#define _LVIZ_CANVAS_CIRCLE_H

#include "curve.h"
#include "vertex.h"

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

class Circle : public Curve {
public:
  Circle(const glm::vec3 &center, const glm::vec3 &normal, glm::f32 radius);

private:
  glm::vec3 center_;
  glm::vec3 normal_;
  glm::f32 radius_;
};

} // namespace canvas
} // namespace lviz

#endif
