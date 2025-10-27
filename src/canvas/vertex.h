#ifndef _LVIZ_CANVAS_VERTEX_H
#define _LVIZ_CANVAS_VERTEX_H

#include "../gp/glm.h"

namespace lviz {
namespace canvas {

struct Vertex {
  gp::Pnt coord;
  gp::Vec normal;

  Vertex() : coord(), normal() {}

  Vertex(const gp::Pnt &coord) : coord(coord), normal() {}

  Vertex(const gp::Pnt &coord, const gp::Vec &normal)
      : coord(coord), normal(normal) {}
};

} // namespace canvas
} // namespace lviz

#endif
