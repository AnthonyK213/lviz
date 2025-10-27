#include "circle.h"
#include "math.h"

#include "../render/gl_vertex_array_buffer.h"

#include <glad/glad.h>

#include <vector>

namespace lviz {
namespace canvas {

static std::vector<Vertex> circleVertices(const glm::vec3 &center,
                                          const glm::vec3 &normal,
                                          glm::f32 radius) {
  glm::vec3 x_dir = glm::cross(glm::vec3(0.0, 1.0, 0.0), normal);
  if (glm::length(x_dir) > 1e-6)
    x_dir = glm::normalize(x_dir);
  else
    x_dir = glm::vec3(1.0, 0.0, 0.0);
  glm::vec3 y_dir = glm::normalize(glm::cross(normal, x_dir));

  glm::f32 theta = std::acos(1.0f - (Math::LinearDeflection() / radius));
  theta = (std::min)(theta, Math::AngularDeflection() * 0.5f);
  int n_vertices = static_cast<int>(std::ceilf(Math::Pi() / theta));

  std::vector<Vertex> vertices{};
  vertices.reserve(n_vertices);
  glm::f32 angle = 0.0f;
  glm::f32 step = 2.0 * Math::Pi() / n_vertices;
  for (int i = 0; i < n_vertices; ++i) {
    glm::vec3 p = x_dir * std::cos(angle) + y_dir * std::sin(angle);
    vertices.emplace_back(p);
    angle += step;
  }

  return vertices;
}

Circle::Circle(const glm::vec3 &center, const glm::vec3 &normal,
               glm::f32 radius)
    : Curve(), center_(center), normal_(normal), radius_(radius) {
  normal_ = glm::normalize(normal_);
  std::vector<Vertex> vertices = circleVertices(center_, normal_, radius_);
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
}

} // namespace canvas
} // namespace lviz
