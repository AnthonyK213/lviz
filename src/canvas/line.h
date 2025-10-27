#ifndef _LVIZ_CANVAS_LINE_H
#define _LVIZ_CANVAS_LINE_H

#include "curve.h"
#include "vertex.h"

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

class Line : public Curve {
public:
  Line(const glm::vec3 &point1, const glm::vec3 &point2);

private:
  canvas::Vertex vertices_[2];
};

} // namespace canvas
} // namespace lviz

#endif
