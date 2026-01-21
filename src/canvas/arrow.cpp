#include "arrow.h"

#include "../render/gl_vertex_buffer_layout.h"
#include "../render/gl_vertex_index_buffer.h"
#include "../util/math.h"

#include <glm/gtc/matrix_transform.hpp>

namespace lviz {
namespace canvas {

Arrow::Arrow(const gp::Pnt &location, const gp::Vec &vector, glm::f32 tip_angle,
             glm::f32 tip_length, int n_fins)
    : buffer_(nullptr), vertices_(), vec_(vector), tip_ang_(tip_angle),
      tip_len_(tip_length), n_fins_(n_fins) {
  if (tip_ang_ <= util::Math::Zero() || tip_ang_ >= util::Math::Pi())
    tip_ang_ = util::Math::Pi() / 6.f;

  glm::f32 vec_len = glm::length(vector);
  if (vec_len <= util::Math::Zero())
    return;
  gp::Vec dir = vector / vec_len;
  glm::f32 tip_len_max = vec_len * 0.382f;
  if (tip_len_ > tip_len_max || tip_len_ <= util::Math::Zero())
    tip_len_ = tip_len_max;

  if (n_fins_ < 2)
    n_fins_ = 2;

  vertices_.reserve(n_fins_ + 3);
  vertices_.push_back({location});
  vertices_.push_back({location + vec_});
  vertices_.push_back({location + (vec_len - tip_len_ * 0.5f) * dir});

  gp::Vec ref_dir = glm::cross(gp::Vec(0.f, 0.f, 1.f), dir);
  if (glm::length(ref_dir) <= util::Math::Zero())
    ref_dir = gp::Vec(0.f, 1.f, 0.f);
  else
    ref_dir = glm::normalize(ref_dir);

  gp::Pnt tip_bot = (vec_len - tip_len_) * dir;
  gp::Vec tr0 = ::std::tan(tip_ang_ * 0.5f) * tip_len_ * ref_dir;
  gp::Pnt fin0 = tip_bot + tr0;
  if (n_fins_ == 2) {
    gp::Pnt fin1 = tip_bot - tr0;
    vertices_.push_back({location + fin0});
    vertices_.push_back({location + fin1});
  } else {
    glm::f32 a = util::Math::Pi() * 2.f / (glm::f32)n_fins_;
    glm::vec4 fin0_4 = glm::vec4(fin0, 1.0f);
    for (int i = 0; i < n_fins_; ++i) {
      glm::vec4 fin_4 = glm::rotate(glm::mat4(1.0f), a * i, dir) * fin0_4;
      vertices_.push_back({location + gp::Pnt(fin_4)});
    }
  }
}

Presentable::Type Arrow::GetType() const {
  return Presentable::Type::Arrow;
}

gp::Box Arrow::GetBox() const {
  return gp::Box();
}

bool Arrow::CreateBuffers() {
  if (vertices_.empty())
    return false;

  std::vector<glm::u32> indices{};
  indices.reserve(n_fins_ * 2 + 2);
  indices.push_back(0);
  indices.push_back(2);
  for (int i = 0; i < n_fins_; ++i) {
    indices.push_back(i + 3);
    indices.push_back((i % 2) + 1);
  }

  buffer_ = std::make_unique<render::GLVertexIndexBuffer<Vertex>>(
      util::span(vertices_), util::span(indices));

  return true;
}

void Arrow::Draw() {
  if (buffer_)
    buffer_->Draw(GL_LINE_STRIP);
}

} // namespace canvas
} // namespace lviz
