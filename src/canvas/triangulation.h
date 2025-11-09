#ifndef _LVIZ_CANVAS_TRIANGULATION_H
#define _LVIZ_CANVAS_TRIANGULATION_H

#include "handle.h"
#include "triangle.h"

#include <vector>

namespace lviz {
namespace canvas {

class Triangulation : public Surface {
public:
  Triangulation();

  ~Triangulation();

  const std::vector<VertexWithNormal> &GetVertices() const {
    return vertices_;
  }

  void PushTriangle(const gp::Pnt &point1, const gp::Pnt &point2,
                    const gp::Pnt &point3);

  void PushTriangle(const gp::Pnt &point1, const gp::Pnt &point2,
                    const gp::Pnt &point3, const gp::Vec &normal1,
                    const gp::Vec &normal2, const gp::Vec &normal3);

  void PushTriangle(const canvas::handle<canvas::Triangle> &triangle);

  void Clear();

  virtual bool CreateBuffers() override;

  virtual gp::Box GetBox() const override;

private:
  std::vector<VertexWithNormal> vertices_;
};

} // namespace canvas
} // namespace lviz

#endif
