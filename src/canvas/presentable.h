#ifndef _LVIZ_CANVAS_PRESENTABLE_H
#define _LVIZ_CANVAS_PRESENTABLE_H

#include "object.h"

#include "../gp/box.h"

namespace lviz {
namespace canvas {

class Presentable : public Object {
public:
  enum class Type {
    None,
    Point,
    Curve,
    Surface,
    Grid,
    Text,
  };

public:
  virtual Type GetType() const = 0;

  virtual gp::Box GetBox() const = 0;

  virtual bool CreateBuffers() = 0;

  virtual void Draw() = 0;
};

} // namespace canvas
} // namespace lviz

#endif
