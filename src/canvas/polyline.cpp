#include "polyline.h"

#include <glad/glad.h>

namespace lviz {
namespace canvas {

Polyline::Polyline(std::vector<glm::vec3> &&vertices)
    : vertex_buffer_(nullptr), vertices_(std::move(vertices)) {
  vertex_buffer_ = std::make_unique<render::GLVertexBuffer>();
  vertex_buffer_->CreateBuffers(vertices_.size(), vertices_.data());
}

Polyline::~Polyline() {}

void Polyline::UpdateShader(render::Shader *shader) {}

void Polyline::Draw() {
  vertex_buffer_->Draw(GL_LINE_STRIP, vertices_.size());
}

} // namespace canvas
} // namespace lviz
