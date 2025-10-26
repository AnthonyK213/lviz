#include "curve.h"

namespace lviz {
namespace canvas {

Curve::Curve() : Geometry(), vertex_buffer_(nullptr) {}

void Curve::UpdateShader(render::Shader *shader) {}

void Curve::Draw() {
  vertex_buffer_->Draw(GL_LINE_STRIP);
}

} // namespace canvas
} // namespace lviz
