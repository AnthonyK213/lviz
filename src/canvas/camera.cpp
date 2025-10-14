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
  UpdateViewCenter();
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

void Camera::UpdateViewCenter() {
  glm::vec3 o(pos_[3]);
  glm::vec3 z(pos_[2]);
  cen_ = o - z * dist_;
}

void Camera::SetAspect(glm::f32 aspect) {
  aspect_ = aspect;
  UpdateProjMatrix();
}

void Camera::Pan(glm::f32 dx, glm::f32 dy) {
  pos_[3] += pos_[0] * dx;
  pos_[3] += pos_[1] * dy;
  UpdateViewMatrix();
  UpdateViewCenter();
}

void Camera::Orbit(glm::f32 rz, glm::f32 pitch) {
  pos_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
  pos_ = glm::rotate(pos_, pitch, glm::vec3{1.0f, 0.0f, 0.0f});
  pos_ = glm::rotate(glm::mat4(1.0f), rz, glm::vec3{0.0f, 0.0f, 1.0f}) * pos_;
  pos_[3] = glm::vec4(cen_, 1.0f) + pos_[2] * dist_;
  UpdateViewMatrix();
}

void Camera::Zoom(glm::f32 delta) {
  glm::f32 new_dist = dist_ + delta;
  if (new_dist <= near_)
    return;
  dist_ = new_dist;
  pos_[3] += pos_[2] * delta;
  UpdateViewMatrix();
}

} // namespace canvas
} // namespace lviz
