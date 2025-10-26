#ifndef _LVIZ_CANVAS_CURVE_H
#define _LVIZ_CANVAS_CURVE_H

#include "geometry.h"

#include "../render/gl_vertex_buffer.h"

#include <memory>

namespace lviz {
namespace canvas {

class Curve : public Geometry {
public:
  virtual void UpdateShader(render::Shader *shader) override;

  virtual void Draw() override;

protected:
  Curve();

protected:
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
};

} // namespace canvas
} // namespace lviz

#endif
