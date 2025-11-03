#include "surface.h"

namespace lviz {
namespace canvas {

Surface::Surface() : Geometry(), vertex_buffer_(nullptr) {}

Presentable::Type Surface::GetType() const {
  return Type::Surface;
}

void Surface::Draw() {
  if (vertex_buffer_)
    vertex_buffer_->Draw(GL_TRIANGLES);
}

} // namespace canvas
} // namespace lviz
