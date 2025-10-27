#ifndef _LVIZ_CANVAS_POLYLINE_H
#define _LVIZ_CANVAS_POLYLINE_H

#include "curve.h"
#include "vertex.h"

#include "../gp/glm.h"

#include <vector>

namespace lviz {
namespace canvas {

class Polyline : public Curve {
public:
  Polyline(const std::vector<gp::Pnt> &vertices);

private:
  std::vector<canvas::Vertex> vertices_;
};

} // namespace canvas
} // namespace lviz

#endif
