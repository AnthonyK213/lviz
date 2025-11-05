#ifndef _LVIZ_CANVAS_VERTEX_H
#define _LVIZ_CANVAS_VERTEX_H

#include "../gp/xyz.h"
#include "../render/gl_vertex_buffer_layout.h"

namespace lviz {
namespace canvas {

struct Vertex {
  gp::Pnt coord;

  Vertex();

  Vertex(const gp::Pnt &coord);

  static const render::GLVertexBufferLayout &GetLayout();
};

} // namespace canvas
} // namespace lviz

#endif
