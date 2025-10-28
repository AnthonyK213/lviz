#include "circle.h"
#include "util.h"

#include "../render/gl_vertex_array_buffer.h"

#include <glad/glad.h>

#include <vector>

namespace lviz {
namespace canvas {

static std::vector<Vertex> circleVertices(const gp::Ax2 &position,
                                          glm::f32 radius) {
  glm::f32 cos_theta = 1.0f - (Math::LinearDeflection() / radius);
  glm::f32 theta = Math::AngularDeflection() * 0.5f;
  if (cos_theta > 0.0)
    theta = (std::min)(theta, std::acos(cos_theta));
  int n_vertices = static_cast<int>(std::ceil(Math::Pi() / theta));

  std::vector<Vertex> vertices{};
  vertices.reserve(n_vertices + 1);
  glm::f32 angle = 0.0f;
  glm::f32 step = Math::Tau() / n_vertices;
  for (int i = 0; i <= n_vertices; ++i) {
    gp::Pnt p = position.Evaluate(std::cos(angle) * radius,
                                  std::sin(angle) * radius, 0.0f);
    vertices.emplace_back(p);
    angle += step;
  }

  return vertices;
}

Circle::Circle(const gp::Ax2 &position, glm::f32 radius)
    : Curve(), pos_(position), radius_(radius) {
  std::vector<Vertex> vertices = circleVertices(pos_, radius_);
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
}

} // namespace canvas
} // namespace lviz
