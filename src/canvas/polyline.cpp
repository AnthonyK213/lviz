#include "polyline.h"

#include <glad/glad.h>

#include <algorithm>
#include <iterator>

namespace lviz {
namespace canvas {

Polyline::Polyline(const std::vector<glm::vec3> &coords)
    : vertex_buffer_(nullptr), vertices_() {
  vertices_.reserve(coords.size());
  std::transform(coords.cbegin(), coords.cend(), std::back_inserter(vertices_),
                 [](const glm::vec3 &coord) {
                   return Vertex{coord, glm::vec3(0.0f, 0.0f, 1.0f)};
                 });
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
