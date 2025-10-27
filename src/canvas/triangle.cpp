#include "triangle.h"

#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Triangle::Triangle(const gp::Pnt &point1, const gp::Pnt &point2,
                   const gp::Pnt &point3)
    : Surface(), vertices_() {
  gp::Vec u = point2 - point1;
  gp::Vec v = point3 - point2;
  gp::Vec normal = glm::normalize(glm::cross(u, v));
  vertices_[0] = {point1, normal};
  vertices_[1] = {point2, normal};
  vertices_[2] = {point3, normal};
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(3, vertices_);
}

Triangle::Triangle(const gp::Pnt &point1, const gp::Pnt &point2,
                   const gp::Pnt &point3, const gp::Vec &normal1,
                   const gp::Vec &normal2, const gp::Vec &normal3)
    : Surface(), vertices_() {
  vertices_[0] = {point1, normal1};
  vertices_[1] = {point2, normal2};
  vertices_[2] = {point3, normal3};
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(3, vertices_);
}

} // namespace canvas
} // namespace lviz
