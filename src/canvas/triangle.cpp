#include "triangle.h"

namespace lviz {
namespace canvas {

Triangle::Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
                   const glm::vec3 &point3)
    : vertex_buffer_(), vertices_() {
  vertices_[0] = point1;
  vertices_[1] = point2;
  vertices_[2] = point3;
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
