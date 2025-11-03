#include "camera.h"

#include "../gp/box.h"

#include <glm/gtc/matrix_transform.hpp>

namespace lviz {
namespace canvas {

Camera::Camera(const glm::mat4 &pos, glm::f32 dist, glm::f32 fovy,
               glm::f32 aspect, glm::f32 near, glm::f32 far)
    : pos_(pos), dist_(dist), fovy_(fovy), aspect_(aspect), near_(near),
      far_(far), proj_type_(ProjectionType::Orthographic) {
  UpdateViewMatrix();
  UpdateProjMatrix();
  UpdateViewCenter();
}

void Camera::UpdateViewMatrix() {
  view_mat_ = glm::inverse(pos_);
}

void Camera::UpdateProjMatrix() {
  switch (proj_type_) {
  case ProjectionType::Orthographic: {
    glm::f32 y = dist_ * std::tan(fovy_ * 0.5f);
    glm::f32 x = y * aspect_;
    proj_mat_ = glm::ortho(-x, x, -y, y, near_, far_);
  } break;
  case ProjectionType::Perspective: {
    proj_mat_ = glm::perspective(fovy_, aspect_, near_, far_);
  } break;
  default:
    break;
  }
}

void Camera::UpdateViewCenter() {
  glm::vec3 o(pos_[3]);
  glm::vec3 z(pos_[2]);
  cen_ = o - z * dist_;
}

void Camera::SetAspect(glm::f32 x, glm::f32 y) {
  aspect_ = x / y;
  UpdateProjMatrix();
}

void Camera::Pan(glm::f32 dx, glm::f32 dy) {
  pos_[3] += pos_[0] * dx * dist_;
  pos_[3] += pos_[1] * dy * dist_;
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

void Camera::ZoomToBox(const gp::Box &box, glm::f32 offse_ratio) {
  std::vector<gp::Pnt> corners = box.Corners();
  if (corners.empty()) {
    return;
  }

  gp::Box view_box{};
  for (const gp::Pnt &corner : corners) {
    gp::Pnt view_corner = view_mat_ * glm::vec4(corner, 1.0);
    view_box.Unite(view_corner);
  }

  cen_ = box.Center();
  glm::f32 max_y = (std::max)((view_box.Max().x - view_box.Min().x) / aspect_,
                              view_box.Max().y - view_box.Min().y);
  max_y *= (1.0f + offse_ratio);
  dist_ = max_y * 0.5f / std::tan(fovy_ * 0.5f);
  pos_[3] = glm::vec4(cen_, 1.0f) + pos_[2] * dist_;

  UpdateViewMatrix();
}

} // namespace canvas
} // namespace lviz
