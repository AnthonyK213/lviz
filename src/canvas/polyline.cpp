#include "polyline.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

#include <algorithm>
#include <iterator>

namespace lviz {
namespace canvas {

Polyline::Polyline(const std::vector<gp::Pnt> &vertices)
    : Curve(), vertices_() {
  vertices_.reserve(vertices.size());
  std::transform(vertices.cbegin(), vertices.cend(),
                 std::back_inserter(vertices_),
                 [](const gp::Pnt &coord) { return Vertex{coord}; });
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices_.size()), vertices_.data());
}

glm::f32 Polyline::T0() const {
  return 0.0f;
}

glm::f32 Polyline::T1() const {
  return static_cast<glm::f32>((std::max)(vertices_.size() - 1, (size_t)0));
}

gp::Pnt Polyline::Value(glm::f32 t) const {
  if (t < T0() || t > T1())
    return gp::UnsetXYZ();

  glm::f32 t_i = std::floor(t);
  glm::f32 t_f = t - t_i;
  int i = static_cast<int>(t_i);

  if (i == vertices_.size() - 1)
    return vertices_[i].coord;
  else
    return vertices_[i].coord * (1 - t_f) + vertices_[i + 1].coord * t_f;
}

bool Polyline::IsClosed() const {
  return false;
}

bool Polyline::IsPeriodic() const {
  return false;
}

glm::f32 Polyline::Period() const {
  return gp::Math::UnsetFloat();
}

} // namespace canvas
} // namespace lviz
