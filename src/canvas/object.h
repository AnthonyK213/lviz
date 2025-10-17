#ifndef _LVIZ_CANVAS_OBJECT_H
#define _LVIZ_CANVAS_OBJECT_H

#include "../render/shader.h"

namespace lviz {
namespace canvas {

class Object {
public:
  virtual ~Object() = default;

  virtual void UpdateShader(render::Shader *shader) = 0;
};

} // namespace canvas
} // namespace lviz

#endif
