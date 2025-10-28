#ifndef _LVIZ_CANVAS_CIRCLE_H
#define _LVIZ_CANVAS_CIRCLE_H

#include "curve.h"

#include "../gp/ax2.h"

namespace lviz {
namespace canvas {

class Circle : public Curve {
public:
  Circle(const gp::Ax2 &position, glm::f32 radius);

  virtual glm::f32 T0() const override;

  virtual glm::f32 T1() const override;

  virtual gp::Pnt Value(glm::f32 t) const override;

  virtual bool IsClosed() const override;

  virtual bool IsPeriodic() const override;

  virtual glm::f32 Period() const override;

  virtual std::vector<Vertex> GetVertices(glm::f32 t0,
                                          glm::f32 t1) const override;

private:
  gp::Ax2 pos_;
  glm::f32 radius_;
};

} // namespace canvas
} // namespace lviz

#endif
