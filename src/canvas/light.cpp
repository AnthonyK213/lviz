#include "light.h"
#include "camera.h"

namespace lviz {
namespace canvas {

Light::Light(const glm::vec3 &pos)
    : camera_(nullptr), offset_(0.0f), pos_(pos), color_(1.0f, 1.0f, 1.0f) {}

Light::~Light() {}

void Light::AttachToCamera(const Camera *camera, const glm::vec3 offset) {
  camera_ = camera;
  offset_ = offset;
}

void Light::UpdateShader(render::Shader *shader) {
  if (camera_) {
    glm::vec3 loc_pos = offset_ * camera_->GetDistance();
    pos_ = camera_->GetPosition() * glm::vec4(loc_pos, 1.0f);
  }

  shader->SetVec3("lightPos", pos_);
  shader->SetVec3("lightColor", color_);
}

} // namespace canvas
} // namespace lviz
