#include "circle.h"
#include "vertex.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

#include <vector>

namespace lviz {
namespace canvas {

static inline gp::Pnt circleValue(const gp::Ax2 &position, glm::f32 radius,
                                  glm::f32 t) {
  return position.Location() + (std::cos(t) * position.XDirection() +
                                std::sin(t) * position.YDirection()) *
                                   radius;
}

static std::vector<Vertex> circleVertices(const gp::Ax2 &position,
                                          glm::f32 radius) {
  glm::f32 cos_theta = 1.0f - (gp::Math::LinearDeflection() / radius);
  glm::f32 theta = gp::Math::AngularDeflection() * 0.5f;
  if (cos_theta > 0.0)
    theta = (std::min)(theta, std::acos(cos_theta));
  int n_vertices = static_cast<int>(std::ceil(gp::Math::Pi() / theta));

  std::vector<Vertex> vertices{};
  vertices.reserve(n_vertices + 1);
  glm::f32 t = 0.0f;
  glm::f32 step = gp::Math::Tau() / n_vertices;
  for (int i = 0; i <= n_vertices; ++i) {
    gp::Pnt p = circleValue(position, radius, t);
    vertices.emplace_back(p);
    t += step;
  }

  return vertices;
}

Circle::Circle(const gp::Ax2 &position, glm::f32 radius)
    : Curve(), pos_(position), radius_(radius) {
  std::vector<Vertex> vertices = circleVertices(pos_, radius_);
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
}

glm::f32 Circle::T0() const {
  return -gp::Math::Infinite();
}

glm::f32 Circle::T1() const {
  return gp::Math::Infinite();
}

gp::Pnt Circle::Value(glm::f32 t) const {
  return circleValue(pos_, radius_, t);
}

bool Circle::IsClosed() const {
  return true;
}

bool Circle::IsPeriodic() const {
  return true;
}

glm::f32 Circle::Period() const {
  return gp::Math::Tau();
}

} // namespace canvas
} // namespace lviz
