#include "surface.h"

namespace lviz {
namespace canvas {

Surface::Surface() : Geometry(), vertex_buffer_(nullptr) {}

void Surface::UpdateShader(render::Shader *shader) {}

void Surface::Draw() {
  vertex_buffer_->Draw(GL_TRIANGLES);
}

} // namespace canvas
} // namespace lviz
