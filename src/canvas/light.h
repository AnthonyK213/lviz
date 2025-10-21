#ifndef _LVIZ_CANVAS_LIGHT_H
#define _LVIZ_CANVAS_LIGHT_H

#include <glm/glm.hpp>

#include "object.h"

namespace lviz {
namespace canvas {

class Camera;

class Light : public Object {
public:
  Light(const glm::vec3 &pos);

  ~Light();

  void AttachToCamera(const Camera *camera, const glm::vec3 offset);

  virtual void UpdateShader(render::Shader *shader) override;

private:
  const Camera *camera_;
  glm::vec3 offset_;
  glm::vec3 pos_;
  glm::vec3 color_;
};

} // namespace canvas
} // namespace lviz

#endif
