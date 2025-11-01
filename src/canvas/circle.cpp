#include "circle.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

Circle::Circle(const gp::Ax2 &position, glm::f32 radius)
    : Curve(), pos_(position), radius_(radius) {}

glm::f32 Circle::T0() const {
  return -gp::Math::Infinite();
}

glm::f32 Circle::T1() const {
  return gp::Math::Infinite();
}

gp::Pnt Circle::Value(glm::f32 t) const {
  return pos_.Location() +
         (std::cos(t) * pos_.XDirection() + std::sin(t) * pos_.YDirection()) *
             radius_;
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

std::vector<Vertex> Circle::GetVertices(glm::f32 t0, glm::f32 t1) const {
  if (t0 >= t1)
    return {};

  glm::f32 cos_theta = 1.0f - (gp::Math::LinearDeflection() / radius_);
  glm::f32 theta = gp::Math::AngularDeflection();
  if (cos_theta > 0.0)
    theta = (std::min)(theta, std::acos(cos_theta) * 2.0f);
  int n_vertices = static_cast<int>(std::ceil((t1 - t0) / theta));

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

bool Circle::CreateBuffers() {
  std::vector<Vertex> vertices = GetVertices(0.0f, Period());
  if (vertices.empty())
    return false;
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
  return true;
}

gp::Box Circle::GetBox() const {
  const gp::Pnt &loc = pos_.Location();
  const gp::Vec &x_dir = pos_.XDirection();
  const gp::Vec &y_dir = pos_.YDirection();
  gp::Vec diag{std::hypot(x_dir.x, y_dir.x), std::hypot(x_dir.y, y_dir.y),
               std::hypot(x_dir.z, y_dir.z)};
  diag *= radius_;
  return gp::Box(loc - diag, loc + diag);
}

} // namespace canvas
} // namespace lviz
