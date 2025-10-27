#ifndef _LVIZ_CANVAS_LINE_H
#define _LVIZ_CANVAS_LINE_H

#include "curve.h"
#include "vertex.h"

#include "../gp/glm.h"

namespace lviz {
namespace canvas {

class Line : public Curve {
public:
  Line(const gp::Pnt &point1, const gp::Pnt &point2);

private:
  canvas::Vertex vertices_[2];
};

} // namespace canvas
} // namespace lviz

#endif
