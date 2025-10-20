#include "triangle.h"

namespace lviz {
namespace canvas {

Triangle::Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
                   const glm::vec3 &point3)
    : vertex_buffer_(), vertices_() {
  glm::vec3 u = point2 - point1;
  glm::vec3 v = point3 - point2;
  glm::vec3 normal = glm::normalize(glm::cross(u, v));
  vertices_[0] = {point1, normal};
  vertices_[1] = {point2, normal};
  vertices_[2] = {point3, normal};
  vertex_buffer_ = std::make_unique<render::GLVertexBuffer>();
  vertex_buffer_->CreateBuffers(3, vertices_);
}

Triangle::Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
                   const glm::vec3 &point3, const glm::vec3 &normal1,
                   const glm::vec3 &normal2, const glm::vec3 &normal3)
    : vertex_buffer_(), vertices_() {
  vertices_[0] = {point1, normal1};
  vertices_[1] = {point2, normal2};
  vertices_[2] = {point3, normal3};
  vertex_buffer_ = std::make_unique<render::GLVertexBuffer>();
  vertex_buffer_->CreateBuffers(3, vertices_);
}

Triangle::~Triangle() {}

void Triangle::UpdateShader(render::Shader *shader) {}

void Triangle::Draw() {
  vertex_buffer_->Draw(GL_TRIANGLES, 3);
}

} // namespace canvas
} // namespace lviz
