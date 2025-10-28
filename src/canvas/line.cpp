#include "line.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Line::Line(const gp::Pnt &point1, const gp::Pnt &point2)
    : Curve(), vertices_() {
  vertices_[0] = {point1};
  vertices_[1] = {point2};
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(2, vertices_);
}

glm::f32 Line::T0() const {
  return 0.0f;
}

glm::f32 Line::T1() const {
  return 1.0f;
}

gp::Pnt Line::Value(glm::f32 t) const {
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

} // namespace canvas
} // namespace lviz
