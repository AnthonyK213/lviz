#ifndef _LVIZ_CANVAS_SURFACE_H
#define _LVIZ_CANVAS_SURFACE_H

#include "geometry.h"

#include "../render/gl_vertex_buffer.h"

#include <memory>

namespace lviz {
namespace canvas {

class Surface : public Geometry {
public:
  virtual void UpdateShader(render::Shader *shader) override;

  virtual void Draw() override;

protected:
  Surface();

protected:
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
};

} // namespace canvas
} // namespace lviz

#endif
