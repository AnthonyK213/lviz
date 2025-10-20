#include "light.h"

namespace lviz {
namespace canvas {

Light::Light(const glm::vec3 &pos) : pos_(pos), color_(1.0f, 1.0f, 1.0f) {}

Light::~Light() {}

void Light::UpdateShader(render::Shader *shader) {
  shader->SetVec3("lightPos", pos_);
  shader->SetVec3("lightColor", color_);
}

} // namespace canvas
} // namespace lviz
