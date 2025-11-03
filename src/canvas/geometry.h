#ifndef _LVIZ_CANVAS_GEOMETRY_H
#define _LVIZ_CANVAS_GEOMETRY_H

#include "presentable.h"

#include "../gp/box.h"

namespace lviz {
namespace canvas {

class Geometry : public Presentable {
public:
  virtual gp::Box GetBox() const = 0;
};

} // namespace canvas
} // namespace lviz

#endif
