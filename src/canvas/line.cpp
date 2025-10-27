#include "line.h"

#include "../render/gl_vertex_array_buffer.h"

#include <glad/glad.h>

namespace lviz {
namespace canvas {

Line::Line(const glm::vec3 &point1, const glm::vec3 &point2)
    : Curve(), vertices_() {
  vertices_[0] = Vertex{point1, glm::vec3(0.0f, 0.0f, 1.0f)};
  vertices_[1] = Vertex{point2, glm::vec3(0.0f, 0.0f, 1.0f)};
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(2, vertices_);
}

} // namespace canvas
} // namespace lviz
