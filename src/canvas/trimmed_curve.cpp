#include "trimmed_curve.h"

#include "../gp/util.h"
#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

TrimmedCurve::TrimmedCurve(const canvas::handle<canvas::Curve> &curve,
                           glm::f32 t0, glm::f32 t1)
    : crv_(curve), t0_(t0), t1_(t1) {}

glm::f32 TrimmedCurve::T0() const {
  return t0_;
}

glm::f32 TrimmedCurve::T1() const {
  return t1_;
}

gp::Pnt TrimmedCurve::Value(glm::f32 t) const {
  if (!Contains(t))
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

std::vector<Vertex> TrimmedCurve::GetVertices(glm::f32 t0, glm::f32 t1) const {
  if (t0 >= t1 || !Contains(t0) || !Contains(t1))
    return {};
  return crv_->GetVertices(t0, t1);
}

bool TrimmedCurve::CreateBuffers() {
  std::vector<Vertex> vertices = GetVertices(t0_, t1_);
  if (vertices.empty())
    return false;
  vertex_buffer_ = std::make_unique<render::GLVertexArrayBuffer>(
      static_cast<int>(vertices.size()), vertices.data());
  return true;
}

gp::Box TrimmedCurve::GetBox() const {
  return crv_->GetBox();
}

} // namespace canvas
} // namespace lviz
