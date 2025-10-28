#ifndef _LVIZ_CANVAS_POLYLINE_H
#define _LVIZ_CANVAS_POLYLINE_H

#include "curve.h"
#include "vertex.h"

#include "../gp/glm.h"

#include <vector>

namespace lviz {
namespace canvas {

class Polyline : public Curve {
public:
  Polyline(const std::vector<gp::Pnt> &vertices);

  virtual glm::f32 T0() const override;

  virtual glm::f32 T1() const override;

  virtual gp::Pnt Value(glm::f32 t) const override;

  virtual bool IsClosed() const override;

  virtual bool IsPeriodic() const override;

  virtual glm::f32 Period() const override;

  virtual std::vector<Vertex> GetVertices(glm::f32 t0,
                                          glm::f32 t1) const override;

private:
  std::vector<canvas::Vertex> vertices_;
};

} // namespace canvas
} // namespace lviz

#endif
