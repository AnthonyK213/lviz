#include "line.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Line::Line(const gp::Pnt &point1, const gp::Pnt &point2)
    : Curve(), vertices_() {
  vertices_[0] = {point1};
  vertices_[1] = {point2};
}

glm::f32 Line::T0() const {
  return 0.0f;
}

glm::f32 Line::T1() const {
  return 1.0f;
}

gp::Pnt Line::Value(glm::f32 t) const {
  if (!Contains(t))
    return gp::UnsetXYZ();
  return vertices_[0].coord * (1.0f - t) + vertices_[1].coord * t;
}

bool Line::IsClosed() const {
  return false;
}

bool Line::IsPeriodic() const {
  return false;
}

glm::f32 Line::Period() const {
  return gp::Math::UnsetFloat();
}

std::vector<Vertex> Line::GetVertices(glm::f32 t0, glm::f32 t1) const {
  if (t0 >= t1 || !Contains(t0) || !Contains(t1))
    return {};
  return {Vertex{Value(t0)}, Vertex{Value(t1)}};
}

bool Line::CreateBuffers() {
  vertex_buffer_ =
      std::make_unique<render::GLVertexArrayBuffer<Vertex>>(2, vertices_);
  return true;
}

gp::Box Line::GetBox() const {
  gp::Box box{};
  box.Unite(vertices_[0].coord);
  box.Unite(vertices_[1].coord);
  return box;
}

} // namespace canvas
} // namespace lviz
