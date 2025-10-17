#ifndef _LVIZ_CANVAS_GEOMETRY_H
#define _LVIZ_CANVAS_GEOMETRY_H

#include "object.h"

namespace lviz {
namespace canvas {

class Geometry : public Object {
public:
  virtual void Draw() = 0;
};

} // namespace canvas
} // namespace lviz

#endif
