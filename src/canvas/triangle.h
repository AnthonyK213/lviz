#ifndef _LVIZ_CANVAS_TRIANGLE_H
#define _LVIZ_CANVAS_TRIANGLE_H

#include "surface.h"
#include "vertex_with_normal.h"

#include <memory>

namespace lviz {
namespace canvas {

class Triangle : public Surface {
public:
  Triangle(const gp::Pnt &point1, const gp::Pnt &point2, const gp::Pnt &point3);

  Triangle(const gp::Pnt &point1, const gp::Pnt &point2, const gp::Pnt &point3,
           const gp::Vec &normal1, const gp::Vec &normal2,
           const gp::Vec &normal3);

  virtual bool CreateBuffers() override;

  virtual gp::Box GetBox() const override;

private:
  VertexWithNormal vertices_[3];
};

} // namespace canvas
} // namespace lviz

#endif
