#ifndef _LVIZ_CANVAS_VERTEX_WITH_NORMAL_H
#define _LVIZ_CANVAS_VERTEX_WITH_NORMAL_H

#include "../gp/xyz.h"
#include "../render/gl_vertex_buffer_layout.h"

namespace lviz {
namespace canvas {

struct VertexWithNormal {
  gp::Pnt coord;
  gp::Vec normal;

  VertexWithNormal();

  VertexWithNormal(const gp::Pnt &coord);

  VertexWithNormal(const gp::Pnt &coord, const gp::Vec &normal);

  static const render::GLVertexBufferLayout &GetLayout();
};

} // namespace canvas
} // namespace lviz

#endif
