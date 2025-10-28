#include "trimmed_curve.h"
#include "vertex.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

#include <vector>

namespace lviz {
namespace canvas {

static std::vector<Vertex>
trimmedCurveVertices(const canvas::handle<canvas::Curve> &curve, glm::f32 t0,
                     glm::f32 t1) {
  std::vector<Vertex> vertices{};
  return vertices;
}

TrimmedCurve::TrimmedCurve(const canvas::handle<canvas::Curve> &curve,
                           glm::f32 t0, glm::f32 t1)
    : crv_(curve), t0_(t0), t1_(t1) {
  std::vector<Vertex> vertices = trimmedCurveVertices(crv_, t0_, t1_);
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
}

glm::f32 TrimmedCurve::T0() const {
  return t0_;
}

glm::f32 TrimmedCurve::T1() const {
  return t1_;
}

gp::Pnt TrimmedCurve::Value(glm::f32 t) const {
  if (t < T0() || t > T1())
    return gp::UnsetXYZ();
  return crv_->Value(t);
}

bool TrimmedCurve::IsClosed() const {
  return false;
}

bool TrimmedCurve::IsPeriodic() const {
  return false;
}

glm::f32 TrimmedCurve::Period() const {
  return gp::Math::UnsetFloat();
}

} // namespace canvas
} // namespace lviz
