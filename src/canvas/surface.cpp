#include "surface.h"

namespace lviz {
namespace canvas {

Surface::Surface() : Geometry(), vertex_buffer_(nullptr) {}

void Surface::UpdateShader(render::Shader *shader) {}

Geometry::GeomType Surface::GetType() const {
  return GeomType::Surface;
}

void Surface::Draw() {
  if (vertex_buffer_)
    vertex_buffer_->Draw(GL_TRIANGLES);
}

} // namespace canvas
} // namespace lviz
