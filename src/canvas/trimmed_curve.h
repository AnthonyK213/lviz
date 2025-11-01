#ifndef _LVIZ_CANVAS_TRIMMED_CURVE_H
#define _LVIZ_CANVAS_TRIMMED_CURVE_H

#include "curve.h"
#include "handle.h"

namespace lviz {
namespace canvas {

class TrimmedCurve : public Curve {
public:
  TrimmedCurve(const canvas::handle<canvas::Curve> &curve, glm::f32 t0,
               glm::f32 t1);

  virtual glm::f32 T0() const override;

  virtual glm::f32 T1() const override;

  virtual gp::Pnt Value(glm::f32 t) const override;

  virtual bool IsClosed() const override;

  virtual bool IsPeriodic() const override;

  virtual glm::f32 Period() const override;

  virtual std::vector<Vertex> GetVertices(glm::f32 t0,
                                          glm::f32 t1) const override;

  virtual bool CreateBuffers() override;

  virtual gp::Box GetBox() const override;

private:
  canvas::handle<canvas::Curve> crv_;
  glm::f32 t0_;
  glm::f32 t1_;
};

} // namespace canvas
} // namespace lviz

#endif
