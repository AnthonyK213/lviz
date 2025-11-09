#include "triangulation.h"

#include "../render/gl_vertex_array_buffer.h"

#include <iostream>

namespace lviz {
namespace canvas {

Triangulation::Triangulation() : Surface(), vertices_() {}

Triangulation::~Triangulation() {}

void Triangulation::PushTriangle(const gp::Pnt &point1, const gp::Pnt &point2,
                                 const gp::Pnt &point3) {
  gp::Vec u = point2 - point1;
  gp::Vec v = point3 - point2;
  gp::Vec normal = glm::normalize(glm::cross(u, v));
  vertices_.emplace_back(point1, normal);
  vertices_.emplace_back(point2, normal);
  vertices_.emplace_back(point3, normal);
}

void Triangulation::PushTriangle(const gp::Pnt &point1, const gp::Pnt &point2,
                                 const gp::Pnt &point3, const gp::Vec &normal1,
                                 const gp::Vec &normal2,
                                 const gp::Vec &normal3) {
  vertices_.emplace_back(point1, normal1);
  vertices_.emplace_back(point2, normal2);
  vertices_.emplace_back(point3, normal3);
}

void Triangulation::PushTriangle(
    const canvas::handle<canvas::Triangle> &triangle) {
  const VertexWithNormal *vertices = triangle->GetVertices();
  for (int i = 0; i < 3; ++i) {
    vertices_.push_back(vertices[i]);
  }
}

void Triangulation::Clear() {
  vertices_.clear();
}

bool Triangulation::CreateBuffers() {
  vertex_buffer_ =
      std::make_unique<render::GLVertexArrayBuffer<VertexWithNormal>>(
          vertices_.size(), vertices_.data());
  return true;
}

gp::Box Triangulation::GetBox() const {
  gp::Box box{};
  for (const VertexWithNormal &vertex : vertices_) {
    box.Unite(vertex.coord);
  }
  return box;
}

} // namespace canvas
} // namespace lviz
