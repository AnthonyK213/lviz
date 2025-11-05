#include "view3d.h"

#include "../util/math.h"

#include "../window/window.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace lviz {
namespace ui {

static const char *PNT_VS = R"(
#version 330 core

layout(location = 0) in vec3 aCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(aCoord, 1.0f);
}
)";

static const char *PNT_FS = R"(
#version 330 core

out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

static const char *PNT_GS = R"(
#version 330 core

uniform vec2 ndcUnit;
uniform float pntSize;

layout (points) in;
layout (line_strip, max_vertices = 5) out;

void build_cross(vec4 position) {
  vec2 crsSize = pntSize * 0.5f * position.w * ndcUnit;
  gl_Position = position + vec4(-crsSize.x, 0.0f, 0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(crsSize.x, 0.0f, 0.0f, 0.0f);
  EmitVertex();
  gl_Position = position;
  EmitVertex();
  gl_Position = position + vec4(0.0f, crsSize.y, 0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(0.0f, -crsSize.y, 0.0f, 0.0f);
  EmitVertex();
  EndPrimitive();
}

void main() {
  build_cross(gl_in[0].gl_Position);
}
)";

static const char *CRV_VS = R"(
#version 330 core

layout(location = 0) in vec3 aCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(aCoord, 1.0f);
}
)";

static const char *CRV_FS = R"(
#version 330 core

out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

static const char *SRF_VS = R"(
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

static const char *SRF_FS = R"(
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

static void cameraUpdateShader(canvas::Camera *camera, render::Shader *shader) {
  shader->SetMat4("model", glm::mat4{1.0f});
  shader->SetMat4("view", camera->GetViewMatrix());
  shader->SetMat4("projection", camera->GetProjMatrix());
  shader->SetVec3("viewPos", glm::vec3(camera->GetPosition()[3]));
}

static void lightUpdateShader(canvas::Light *light, render::Shader *shader) {
  shader->SetVec3("lightPos", light->GetPosition());
  shader->SetVec3("lightColor", light->GetColor());
}

inline static glm::mat4 createCameraPos(const glm::vec3 &cam_orig) {
  glm::vec3 cam_x = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), cam_orig);
  glm::vec3 cam_y = glm::cross(cam_orig, cam_x);
  return glm::mat4{glm::vec4(glm::normalize(cam_x), 0.0f),
                   glm::vec4(glm::normalize(cam_y), 0.0f),
                   glm::vec4(glm::normalize(cam_orig), 0.0f),
                   glm::vec4(cam_orig, 1.0f)};
}

View3d::View3d(window::Window *parent, const glm::vec2 &init_size)
    : parent_(parent), size_(init_size), cursor_(0, 0), pnt_size_(10.0f),
      crv_width_(5.0f), show_grid_(false) {
  render::ShaderSource pnt_shader_source{};
  pnt_shader_source.vertex_shader = PNT_VS;
  pnt_shader_source.fragment_shader = PNT_FS;
  pnt_shader_source.geometry_shader = PNT_GS;
  pnt_shader_ = std::make_unique<render::Shader>(pnt_shader_source);

  render::ShaderSource crv_shader_source{};
  crv_shader_source.vertex_shader = CRV_VS;
  crv_shader_source.fragment_shader = CRV_FS;
  crv_shader_ = std::make_unique<render::Shader>(crv_shader_source);

  render::ShaderSource srf_shader_source{};
  srf_shader_source.vertex_shader = SRF_VS;
  srf_shader_source.fragment_shader = SRF_FS;
  srf_shader_ = std::make_unique<render::Shader>(srf_shader_source);

  glm::vec3 cam_orig{40.0f, -20.0f, 20.0f};
  glm::mat4 cam_pos = createCameraPos(cam_orig);
  glm::f32 cam_dist = glm::length(cam_orig);
  camera_ = std::make_unique<canvas::Camera>(
      cam_pos, cam_dist, util::Math::ToRad(45.0f), 1.3f, 0.1f, 1000.0f);

  light_ = std::make_unique<canvas::Light>(glm::vec3(90.0f, -120.0f, 150.0f));
  light_->AttachToCamera(camera_.get(), glm::vec3(-0.35f, 0.35f, 0.0f));

  grid_ = std::make_unique<canvas::Grid>(camera_.get());
  grid_->CreateBuffers();

  font_atlas_ = std::make_unique<text::FontAtlas>();
  font_atlas_->Init("C:/Windows/Fonts/arial.ttf");
}

View3d::~View3d() {}

void View3d::Render() {
  size_ = {parent_->GetWidth(), parent_->GetHeight()};

  camera_->SetAspect(size_.x, size_.y);

  if (!points_.empty()) {
    pnt_shader_->Use();
    cameraUpdateShader(camera_.get(), pnt_shader_.get());
    pnt_shader_->SetVec2("ndcUnit", glm::vec2{2.0f} / size_);
    pnt_shader_->SetNums("pntSize", 1, &pnt_size_);
    for (const canvas::handle<canvas::Presentable> &pnt : points_) {
      pnt->Draw();
    }
  }

  if (!curves_.empty()) {
    crv_shader_->Use();
    cameraUpdateShader(camera_.get(), crv_shader_.get());
    for (const canvas::handle<canvas::Presentable> &crv : curves_) {
      crv->Draw();
    }
  }

  if (!surfaces_.empty()) {
    srf_shader_->Use();
    cameraUpdateShader(camera_.get(), srf_shader_.get());
    lightUpdateShader(light_.get(), srf_shader_.get());
    for (const canvas::handle<canvas::Presentable> &srf : surfaces_) {
      srf->Draw();
    }
  }

  if (!labels_.empty()) {
    for (const canvas::handle<canvas::Presentable> &lbl : labels_) {
      lbl->Draw();
    }
  }

  if (show_grid_) {
    grid_->Draw();
  }
}

void View3d::Clear() {
  points_.clear();
  curves_.clear();
  surfaces_.clear();
}

bool View3d::Display(const canvas::handle<canvas::Presentable> &obj) {
  if (!obj || !obj->CreateBuffers())
    return false;

  switch (obj->GetType()) {
  case canvas::Presentable::Type::Point: {
    points_.push_back(obj);
  } break;
  case canvas::Presentable::Type::Curve: {
    curves_.push_back(obj);
  } break;
  case canvas::Presentable::Type::Surface: {
    surfaces_.push_back(obj);
  } break;
  case canvas::Presentable::Type::Label: {
    labels_.push_back(obj);
  } break;
  default:
    return false;
  }

  return true;
}

void View3d::ZoomAll() {
  gp::Box box{};

  for (const canvas::handle<canvas::Presentable> &obj : points_) {
    box.Unite(obj->GetBox());
  }

  for (const canvas::handle<canvas::Presentable> &obj : curves_) {
    box.Unite(obj->GetBox());
  }

  for (const canvas::handle<canvas::Presentable> &obj : surfaces_) {
    box.Unite(obj->GetBox());
  }

  camera_->ZoomToBox(box, 0.2f);
}

void View3d::Resize(int width, int height) {
  size_.x = width;
  size_.y = height;
}

void View3d::SetShowGrid(bool show_grid) {
  show_grid_ = show_grid;
}

void View3d::OnMouseMove(double x, double y, ui::MouseButton button) {
  ImGuiIO &io = ImGui::GetIO();
  if (io.WantCaptureMouse)
    return;

  double dx = x - cursor_.x;
  double dy = y - cursor_.y;

  switch (button) {
  case ui::MouseButton::Right:
    camera_->Orbit(-dx * 0.008f, -dy * 0.008f);
    break;

  case ui::MouseButton::Middle:
    camera_->Pan(-dx * 0.001f, dy * 0.001f);
    break;

  default:
    break;
  }

  cursor_.x = (glm::f32)x;
  cursor_.y = (glm::f32)y;
}

void View3d::OnMouseWheel(double delta) {
  ImGuiIO &io = ImGui::GetIO();
  if (io.WantCaptureMouse)
    return;
  camera_->Zoom(-delta);
}

} // namespace ui
} // namespace lviz
