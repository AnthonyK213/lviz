#include "vertex.h"

namespace lviz {
namespace canvas {

Vertex::Vertex() : coord() {}

Vertex::Vertex(const gp::Pnt &coord) : coord(coord) {}

const render::GLVertexBufferLayout &Vertex::GetLayout() {
  static render::GLVertexBufferLayout layout{
      {GL_FLOAT, 3, offsetof(Vertex, coord)},
  };
  return layout;
}

} // namespace canvas
} // namespace lviz
