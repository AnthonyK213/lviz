#ifndef _LVIZ_CANVAS_CAMERA_H
#define _LVIZ_CANVAS_CAMERA_H

#include <glm/glm.hpp>

#include "object.h"

namespace lviz {
namespace canvas {

class Camera : public Object {
public:
  Camera(const glm::mat4 &pos, glm::f32 dist, glm::f32 fov, glm::f32 aspect,
         glm::f32 near, glm::f32 far);

  virtual void UpdateShader(render::Shader *shader) override;

  const glm::mat4 &GetViewMatrix() const {
    return view_mat_;
  }

  const glm::mat4 &GetProjMatrix() const {
    return proj_mat_;
  }

  void UpdateViewMatrix();

  void UpdateProjMatrix();

  void UpdateViewCenter();

  void SetAspect(glm::f32 x, glm::f32 y);

  void Pan(glm::f32 dx, glm::f32 dy);

  void Orbit(glm::f32 rz, glm::f32 pitch);

  void Zoom(glm::f32 delta);

private:
  glm::mat4 view_mat_; /* Cached view matrix */
  glm::mat4 proj_mat_; /* Cached projection matrix */

  glm::mat4 pos_;
  glm::vec3 cen_; /* Cached view center */
  glm::f32 dist_;

  glm::f32 fov_;
  glm::f32 aspect_;
  glm::f32 near_;
  glm::f32 far_;
};

} // namespace canvas
} // namespace lviz

#endif
