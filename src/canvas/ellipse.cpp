#include "ellipse.h"
#include "vertex.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

#include <vector>

namespace lviz {
namespace canvas {

static inline gp::Pnt ellipseValue(const gp::Ax2 &position,
                                   glm::f32 major_radius, glm::f32 minor_radius,
                                   glm::f32 t) {
  return position.Location() +
         std::cos(t) * major_radius * position.XDirection() +
         std::sin(t) * minor_radius * position.YDirection();
}

static std::vector<Vertex> ellipseVertices(const gp::Ax2 &position,
                                           glm::f32 major_radius,
                                           glm::f32 minor_radius) {
  /* TODO: Implement with *REAL* deflections. */

  glm::f32 theta = gp::Math::AngularDeflection() * 0.5f;
  int n_vertices = static_cast<int>(std::ceil(gp::Math::Pi() / theta));

  std::vector<Vertex> vertices{};
  vertices.reserve(n_vertices + 1);
  glm::f32 t = 0.0f;
  glm::f32 step = gp::Math::Tau() / n_vertices;
  for (int i = 0; i <= n_vertices; ++i) {
    gp::Pnt p = ellipseValue(position, major_radius, minor_radius, t);
    vertices.emplace_back(p);
    t += step;
  }

  return vertices;
}

Ellipse::Ellipse(const gp::Ax2 &position, glm::f32 major_radius,
                 glm::f32 minor_radius)
    : Curve(), pos_(position), major_(major_radius), minor_(minor_radius) {
  std::vector<Vertex> vertices = ellipseVertices(pos_, major_, minor_);
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
}

glm::f32 Ellipse::T0() const {
  return -gp::Math::Infinite();
}

glm::f32 Ellipse::T1() const {
  return gp::Math::Infinite();
}

gp::Pnt Ellipse::Value(glm::f32 t) const {
  return ellipseValue(pos_, major_, minor_, t);
}

bool Ellipse::IsClosed() const {
  return true;
}

bool Ellipse::IsPeriodic() const {
  return true;
}

glm::f32 Ellipse::Period() const {
  return gp::Math::Tau();
}

} // namespace canvas
} // namespace lviz
