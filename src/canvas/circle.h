#ifndef _LVIZ_CANVAS_CIRCLE_H
#define _LVIZ_CANVAS_CIRCLE_H

#include "curve.h"
#include "vertex.h"

#include "../gp/ax2.h"

namespace lviz {
namespace canvas {

class Circle : public Curve {
public:
  Circle(const gp::Ax2 &position, glm::f32 radius);

private:
  gp::Ax2 pos_;
  glm::f32 radius_;
};

} // namespace canvas
} // namespace lviz

#endif
