#ifndef _LVIZ_CANVAS_POLYLINE_H
#define _LVIZ_CANVAS_POLYLINE_H

#include "curve.h"
#include "vertex.h"

#include <glm/glm.hpp>

#include <vector>

namespace lviz {
namespace canvas {

class Polyline : public Curve {
public:
  Polyline(const std::vector<glm::vec3> &vertices);

private:
  std::vector<canvas::Vertex> vertices_;
};

} // namespace canvas
} // namespace lviz

#endif
