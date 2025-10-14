#include "view3d.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace lviz {
namespace ui {

View3d::View3d() : camera_(nullptr), frame_buffer_(nullptr), size_(800, 600) {
  frame_buffer_ = std::make_unique<render::GLFrameBuffer>();
  frame_buffer_->CreateBuffers(800, 600);

  vertices_ = {{0, 0, 0}, {20, 0, 0}, {0, 40, 0}};
  indices_ = {0, 1, 2};

  vertex_buffer_ = std::make_unique<render::GLVertexBuffer>();
  vertex_buffer_->CreateBuffers(vertices_, indices_);

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
                                             0.1f, 100.0f);
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
  vertex_buffer_->Draw(indices_.size());
  frame_buffer_->Unbind();

  uint64_t tex_id = frame_buffer_->GetTexture();
  ImGui::Image(reinterpret_cast<void *>(tex_id), ImVec2{size_.x, size_.y},
               ImVec2{0, 1}, ImVec2{1, 0});

  ImGui::End();
}

void View3d::Purge() {}

bool View3d::DrawPoint(const glm::vec3 &point) {
  return true;
}

bool View3d::DrawLineSegment(const glm::vec3 &point1, const glm::vec3 &point2) {
  return true;
}

bool View3d::DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                          const glm::vec3 &point3) {
  return true;
}

void View3d::Resize(int width, int height) {
  size_.x = width;
  size_.y = height;

  frame_buffer_->CreateBuffers((int)size_.x, (int)size_.y);
}

void View3d::OnMouseMove(double x, double y, ui::MouseButton button) {}

void View3d::OnMouseWheel(double delta) {}

} // namespace ui
} // namespace lviz
