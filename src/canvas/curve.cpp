#include "curve.h"

namespace lviz {
namespace canvas {

Curve::Curve() : Geometry(), vertex_buffer_(nullptr) {}

bool Curve::Contains(glm::f32 t) const {
  return t >= T0() && t <= T1();
}

void Curve::UpdateShader(render::Shader *shader) {}

Geometry::GeomType Curve::GetType() const {
  return GeomType::Curve;
}

void Curve::Draw() {
  if (vertex_buffer_)
    vertex_buffer_->Draw(GL_LINE_STRIP);
}

} // namespace canvas
} // namespace lviz
