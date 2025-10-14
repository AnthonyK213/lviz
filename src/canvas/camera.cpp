#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace lviz {
namespace canvas {

Camera::Camera(const glm::mat4 &pos, glm::f32 dist, glm::f32 fov,
               glm::f32 aspect, glm::f32 near, glm::f32 far)
    : pos_(pos), dist_(dist), fov_(fov), aspect_(aspect), near_(near),
      far_(far) {
  UpdateViewMatrix();
  UpdateProjMatrix();
}

void Camera::UpdateShader(render::Shader *shader) {
  glm::mat4 model{1.0f};
  shader->SetMat4(model, "model");
  shader->SetMat4(view_mat_, "view");
  shader->SetMat4(proj_mat_, "projection");
}

void Camera::UpdateViewMatrix() {
  view_mat_ = glm::inverse(pos_);
}

void Camera::UpdateProjMatrix() {
  proj_mat_ = glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::SetAspect(glm::f32 aspect) {
  aspect_ = aspect;
  UpdateProjMatrix();
}

} // namespace canvas
} // namespace lviz
