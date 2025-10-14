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

  void SetAspect(glm::f32 aspect);

  void Pan();

  void Orbit();

  void Zoom();

private:
  glm::mat4 view_mat_; /* Cached view matrix */
  glm::mat4 proj_mat_; /* Cached projection matrix */

  glm::mat4 pos_;
  glm::f32 dist_;

  glm::f32 fov_;
  glm::f32 aspect_;
  glm::f32 near_;
  glm::f32 far_;
};

} // namespace canvas
} // namespace lviz

#endif
