#ifndef _LVIZ_CANVAS_GEOMETRY_H
#define _LVIZ_CANVAS_GEOMETRY_H

#include "object.h"

#include "../gp/box.h"

namespace lviz {
namespace canvas {

class Geometry : public Object {
public:
  enum class GeomType {
    None,
    Point,
    Curve,
    Surface,
  };

public:
  virtual GeomType GetType() const = 0;

  virtual bool CreateBuffers() = 0;

  virtual void Draw() = 0;

  virtual gp::Box GetBox() const = 0;
};

} // namespace canvas
} // namespace lviz

#endif
