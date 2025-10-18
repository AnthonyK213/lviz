#include "view3d.h"

#include "../canvas/polyline.h"
#include "../canvas/triangle.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace lviz {
namespace ui {

View3d::View3d(window::Window *parent, const glm::vec2 &init_size)
    : parent_(parent), camera_(nullptr), frame_buffer_(nullptr),
      shader_(nullptr), geometries_(), size_(init_size), cursor_(0, 0) {
  frame_buffer_ = std::make_unique<render::GLFrameBuffer>();
  frame_buffer_->CreateBuffers((int)size_.x, (int)size_.y);

  shader_ = std::make_unique<render::Shader>();
  shader_->Load();

  const glm::f32 sqrt2 = 1.f / std::sqrt(2.f);
  const glm::f32 sqrt3 = 1.f / std::sqrt(3.f);
  const glm::f32 sqrt6 = 1.f / std::sqrt(6.f);

  /* clang-format off */
  glm::f32 cam_pos_data[16] = {
    -sqrt2, sqrt2, 0.0f, 0.0f,
    -sqrt6, -sqrt6, 2.0f * sqrt6, 0.0f,
    sqrt3, sqrt3, sqrt3, 0.0f,
    42.0f, 42.0f, 42.0f, 1.0f,
  };
  /* clang-format on */
  glm::mat4 cam_pos = glm::make_mat4(cam_pos_data);
  glm::f32 cam_dist = 42.0f / sqrt3;
  camera_ = std::make_unique<canvas::Camera>(cam_pos, cam_dist, 45.0f, 1.3f,
                                             0.1f, 1000.0f);
}

View3d::~View3d() {
  shader_->Unload();
}

void View3d::Render() {
  ImGui::Begin("View3d");

  ImVec2 region_size = ImGui::GetContentRegionAvail();
  size_ = {region_size.x, region_size.y};

  shader_->Use();
  camera_->SetAspect(size_.x / size_.y);
  camera_->UpdateShader(shader_.get());

  frame_buffer_->Bind();
  for (const std::unique_ptr<canvas::Geometry> &geom : geometries_) {
    geom->UpdateShader(shader_.get());
    geom->Draw();
  }
  frame_buffer_->Unbind();

  uint64_t tex_id = frame_buffer_->GetTexture();
  ImGui::Image(reinterpret_cast<void *>(tex_id), ImVec2{size_.x, size_.y},
               ImVec2{0, 1}, ImVec2{1, 0});

  ImGui::End();
}

void View3d::Purge() {
  geometries_.clear();
}

bool View3d::DrawPoint(const glm::vec3 &point) {
  return true;
}

bool View3d::DrawLine(const glm::vec3 &point1, const glm::vec3 &point2) {
  std::vector<glm::vec3> vertices{point1, point2};
  auto line = std::make_unique<canvas::Polyline>(std::move(vertices));
  geometries_.push_back(std::move(line));
  return true;
}

bool View3d::DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                          const glm::vec3 &point3) {
  auto triangle = std::make_unique<canvas::Triangle>(point1, point2, point3);
  geometries_.push_back(std::move(triangle));
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
