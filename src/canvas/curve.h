#ifndef _LVIZ_CANVAS_CURVE_H
#define _LVIZ_CANVAS_CURVE_H

#include "geometry.h"

#include "../gp/glm.h"
#include "../render/gl_vertex_buffer.h"

#include <memory>

namespace lviz {
namespace canvas {

class Curve : public Geometry {
public:
  virtual glm::f32 T0() const = 0;

  virtual glm::f32 T1() const = 0;

  virtual bool IsClosed() const = 0;

  virtual bool IsPeriodic() const = 0;

  virtual glm::f32 Period() const = 0;

  virtual gp::Pnt Value(glm::f32 t) const = 0;

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
