#include "view3d.h"

#include "../gp/util.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace lviz {
namespace ui {

static const char *VIEW3D_VS = R"(
#version 330 core

layout(location = 0) in vec3 aCoord;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main() {
  FragPos = vec3(model * vec4(aCoord, 1.0f));
  Normal = mat3(transpose(inverse(model))) * aNormal;

  gl_Position = projection * view * model * vec4(aCoord, 1.0f);
}
)";

static const char *VIEW3D_FS = R"(
#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main() {
  float mateiralAmbient = 0.2f;
  float materialSpecular = 0.5f;
  vec3 materialDiffuse = vec3(0.25f, 0.80f, 0.92f);

  // Ambient
  vec3 ambient = mateiralAmbient * lightColor;

  // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = diff * lightColor;

  // Specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
  vec3 specular = materialSpecular * spec * lightColor;

  vec3 result = (ambient + diffuse + spec) * materialDiffuse;
  FragColor = vec4(result, 1.0f);
}
)";

inline static glm::mat4 createCameraPos(const glm::vec3 &cam_orig) {
  glm::vec3 cam_x = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), cam_orig);
  glm::vec3 cam_y = glm::cross(cam_orig, cam_x);
  return glm::mat4{glm::vec4(glm::normalize(cam_x), 0.0f),
                   glm::vec4(glm::normalize(cam_y), 0.0f),
                   glm::vec4(glm::normalize(cam_orig), 0.0f),
                   glm::vec4(cam_orig, 1.0f)};
}

View3d::View3d(window::Window *parent, const glm::vec2 &init_size)
    : parent_(parent), camera_(nullptr), light_(nullptr),
      frame_buffer_(nullptr), shader_(nullptr), grid_(nullptr), geometries_(),
      size_(init_size), cursor_(0, 0) {
  frame_buffer_ = std::make_unique<render::GLFrameBuffer>();
  frame_buffer_->CreateBuffers((int)size_.x, (int)size_.y);

  shader_ = std::make_unique<render::Shader>(VIEW3D_VS, VIEW3D_FS);

  glm::vec3 cam_orig{40.0f, -20.0f, 20.0f};
  glm::mat4 cam_pos = createCameraPos(cam_orig);
  glm::f32 cam_dist = glm::length(cam_orig);
  camera_ = std::make_unique<canvas::Camera>(
      cam_pos, cam_dist, gp::Math::ToRad(45.0f), 1.3f, 0.1f, 1000.0f);

  light_ = std::make_unique<canvas::Light>(glm::vec3(90.0f, -120.0f, 150.0f));
  light_->AttachToCamera(camera_.get(), glm::vec3(-0.35f, 0.35f, 0.0f));

  grid_ = std::make_unique<canvas::Grid>();
}

View3d::~View3d() {}

void View3d::Render() {
  ImGui::Begin("View3d");

  ImVec2 region_size = ImGui::GetContentRegionAvail();
  size_ = {region_size.x, region_size.y};

  shader_->Use();
  camera_->SetAspect(size_.x, size_.y);
  camera_->UpdateShader(shader_.get());
  light_->UpdateShader(shader_.get());

  frame_buffer_->Bind();
  for (const canvas::handle<canvas::Geometry> &geom : geometries_) {
    geom->UpdateShader(shader_.get());
    geom->Draw();
  }
  grid_->Draw(camera_.get());
  frame_buffer_->Unbind();

  uint64_t tex_id = frame_buffer_->GetTexture();
  ImGui::Image(reinterpret_cast<void *>(tex_id), ImVec2{size_.x, size_.y},
               ImVec2{0, 1}, ImVec2{1, 0});

  ImGui::End();
}

void View3d::Purge() {
  geometries_.clear();
}

bool View3d::AddGeometry(const canvas::handle<canvas::Geometry> &geom) {
  geometries_.push_back(geom);
  return true;
}

void View3d::Resize(int width, int height) {
  size_.x = width;
  size_.y = height;

  frame_buffer_->CreateBuffers((int)size_.x, (int)size_.y);
}

void View3d::OnMouseMove(double x, double y, ui::MouseButton button) {
  double dx = x - cursor_.x;
  double dy = y - cursor_.y;

  switch (button) {
  case ui::MouseButton::Right:
    camera_->Orbit(-dx * 0.008f, -dy * 0.008f);
    break;

  case ui::MouseButton::Middle:
    camera_->Pan(-dx * 0.1f, dy * 0.1f);
    break;

  default:
    break;
  }

  cursor_.x = (glm::f32)x;
  cursor_.y = (glm::f32)y;
}

void View3d::OnMouseWheel(double delta) {
  camera_->Zoom(-delta);
}

} // namespace ui
} // namespace lviz
