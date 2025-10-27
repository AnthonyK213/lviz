#include "line.h"

#include "../render/gl_vertex_array_buffer.h"

#include <glad/glad.h>

namespace lviz {
namespace canvas {

Line::Line(const gp::Pnt &point1, const gp::Pnt &point2)
    : Curve(), vertices_() {
  vertices_[0] = {point1};
  vertices_[1] = {point2};
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(2, vertices_);
}

} // namespace canvas
} // namespace lviz
