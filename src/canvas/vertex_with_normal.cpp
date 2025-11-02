#include "vertex_with_normal.h"

namespace lviz {
namespace canvas {

VertexWithNormal::VertexWithNormal() : coord(), normal() {}

VertexWithNormal::VertexWithNormal(const gp::Pnt &coord)
    : coord(coord), normal() {}

VertexWithNormal::VertexWithNormal(const gp::Pnt &coord, const gp::Vec &normal)
    : coord(coord), normal(normal) {}

const render::GLVertexBufferLayout &VertexWithNormal::GetLayout() {
  static render::GLVertexBufferLayout layout{
      {GL_FLOAT, 3, offsetof(VertexWithNormal, coord)},
      {GL_FLOAT, 3, offsetof(VertexWithNormal, normal)},
  };
  return layout;
}

} // namespace canvas
} // namespace lviz
