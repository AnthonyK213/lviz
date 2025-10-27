#include "polyline.h"

#include "../render/gl_vertex_array_buffer.h"

#include <glad/glad.h>

#include <algorithm>
#include <iterator>

namespace lviz {
namespace canvas {

Polyline::Polyline(const std::vector<glm::vec3> &vertices)
    : Curve(), vertices_() {
  vertices_.reserve(vertices.size());
  std::transform(vertices.cbegin(), vertices.cend(),
                 std::back_inserter(vertices_), [](const glm::vec3 &coord) {
                   return Vertex{coord, glm::vec3(0.0f, 0.0f, 1.0f)};
                 });
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices_.size()), vertices_.data());
}

} // namespace canvas
} // namespace lviz
