#include "point.h"

#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Point::Point(const gp::Pnt &coord) : Geometry(), vertex_(coord) {}

void Point::UpdateShader(render::Shader *shader) {}

bool Point::CreateBuffers() {
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(1, &vertex_);
  return true;
}

Geometry::GeomType Point::GetType() const {
  return GeomType::Point;
}

void Point::Draw() {
  if (vertex_buffer_)
    vertex_buffer_->Draw(GL_POINTS);
}

} // namespace canvas
} // namespace lviz
