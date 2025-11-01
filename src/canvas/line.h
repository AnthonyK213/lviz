#ifndef _LVIZ_CANVAS_LINE_H
#define _LVIZ_CANVAS_LINE_H

#include "curve.h"
#include "vertex.h"

#include "../gp/glm.h"

namespace lviz {
namespace canvas {

class Line : public Curve {
public:
  Line(const gp::Pnt &point1, const gp::Pnt &point2);

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
  canvas::Vertex vertices_[2];
};

} // namespace canvas
} // namespace lviz

#endif
