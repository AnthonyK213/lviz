#include "ellipse.h"

#include "../render/gl_vertex_array_buffer.h"
#include "../util/math.h"

namespace lviz {
namespace canvas {

Ellipse::Ellipse(const gp::Ax2 &position, glm::f32 major_radius,
                 glm::f32 minor_radius)
    : Curve(), pos_(position), major_(major_radius), minor_(minor_radius) {}

glm::f32 Ellipse::T0() const {
  return -util::Math::Infinite();
}

glm::f32 Ellipse::T1() const {
  return util::Math::Infinite();
}

gp::Pnt Ellipse::Value(glm::f32 t) const {
  return pos_.Location() + std::cos(t) * major_ * pos_.XDirection() +
         std::sin(t) * minor_ * pos_.YDirection();
}

bool Ellipse::IsClosed() const {
  return true;
}

bool Ellipse::IsPeriodic() const {
  return true;
}

glm::f32 Ellipse::Period() const {
  return util::Math::Tau();
}

std::vector<Vertex> Ellipse::GetVertices(glm::f32 t0, glm::f32 t1) const {
  if (t0 >= t1)
    return {};

  /* TODO: Implement with *REAL* deflections. */

  int n_vertices =
      static_cast<int>(std::ceil((t1 - t0) / util::Math::AngularDeflection()));

  std::vector<Vertex> vertices{};
  vertices.reserve(n_vertices + 1);
  glm::f32 t = t0;
  glm::f32 step = (t1 - t0) / n_vertices;
  for (int i = 0; i <= n_vertices; ++i) {
    vertices.emplace_back(Value(t));
    t += step;
  }

  return vertices;
}

bool Ellipse::CreateBuffers() {
  std::vector<Vertex> vertices = GetVertices(0.0f, Period());
  if (vertices.empty())
    return false;
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer<Vertex>>(
      util::span(vertices));
  return true;
}

gp::Box Ellipse::GetBox() const {
  const gp::Pnt &loc = pos_.Location();
  const gp::Vec &x_dir = pos_.XDirection();
  const gp::Vec &y_dir = pos_.YDirection();
  gp::Vec diag{std::hypot(x_dir.x * major_, y_dir.x * minor_),
               std::hypot(x_dir.y * major_, y_dir.y * minor_),
               std::hypot(x_dir.z * major_, y_dir.z * minor_)};
  return gp::Box(loc - diag, loc + diag);
}

} // namespace canvas
} // namespace lviz
