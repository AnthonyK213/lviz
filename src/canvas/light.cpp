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

glm::vec3 Light::GetPosition() const {
  if (camera_) {
    glm::vec3 loc_pos = offset_ * camera_->GetDistance();
    return camera_->GetPosition() * glm::vec4(loc_pos, 1.0f);
  }
  return pos_;
}

} // namespace canvas
} // namespace lviz
