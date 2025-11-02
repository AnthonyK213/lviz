#include "point.h"

#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Point::Point(const gp::Pnt &coord) : Geometry(), vertex_(coord) {}

Point::Point(glm::f32 x, glm::f32 y, glm::f32 z)
    : Geometry(), vertex_(gp::Pnt(x, y, z)) {}

void Point::UpdateShader(render::Shader *shader) {}

bool Point::CreateBuffers() {
  vertex_buffer_ =
      std::make_unique<render::GLVertexArrayBuffer<Vertex>>(1, &vertex_);
  return true;
}

Geometry::GeomType Point::GetType() const {
  return GeomType::Point;
}

void Point::Draw() {
  if (vertex_buffer_)
    vertex_buffer_->Draw(GL_POINTS);
}

gp::Box Point::GetBox() const {
  return gp::Box(vertex_.coord, vertex_.coord);
}

} // namespace canvas
} // namespace lviz
