#include "label.h"

#include "../render/gl_vertex_array_buffer.h"

namespace lviz {
namespace canvas {

LabelVertex::LabelVertex(const glm::vec2 &coord, const glm::vec2 &uv)
    : coord(coord), uv(uv) {}

const render::GLVertexBufferLayout &LabelVertex::GetLayout() {
  static render::GLVertexBufferLayout layout{
      {GL_FLOAT, 2, offsetof(LabelVertex, coord)},
      {GL_FLOAT, 2, offsetof(LabelVertex, uv)},
  };
  return layout;
}

Label::Label(const std::string &text, const gp::Pnt &location, glm::f32 size)
    : txt_(text), loc_(location), size_(size) {}

void Label::BuildGlyphs(const text::FontAtlas *font_atlas) {
  vertices_.clear();
  vertices_.reserve(txt_.length() * 6);

  glm::f32 x = 0.0f, y = 0.0f;
  for (char c : txt_) {
    const text::Character *ch = font_atlas->GetCharacter(c);
    if (!ch)
      ch = font_atlas->GetCharacter('?');
    if (!ch)
      continue;

    glm::f32 xpos = x + ch->bearing.x;
    glm::f32 ypos = y - (ch->size.y - ch->bearing.y);
    glm::f32 w = ch->size.x;
    glm::f32 h = ch->size.y;

    glm::vec2 uv01{ch->top_left.x, ch->bot_right.y};
    glm::vec2 uv10{ch->bot_right.x, ch->top_left.y};

    vertices_.emplace_back(glm::vec2(xpos, ypos + h), ch->top_left);
    vertices_.emplace_back(glm::vec2(xpos, ypos), uv01);
    vertices_.emplace_back(glm::vec2(xpos + w, ypos), ch->bot_right);
    vertices_.emplace_back(glm::vec2(xpos, ypos + h), ch->top_left);
    vertices_.emplace_back(glm::vec2(xpos + w, ypos), ch->bot_right);
    vertices_.emplace_back(glm::vec2(xpos + w, ypos + h), uv10);

    x += (ch->advance >> 6);
  }
}

Presentable::Type Label::GetType() const {
  return Type::Label;
}

gp::Box Label::GetBox() const {
  return gp::Box();
}

bool Label::CreateBuffers() {
  if (vertices_.empty())
    return false;

  buffer_ =
      std::make_unique<render::GLVertexArrayBuffer<LabelVertex>>(vertices_);

  return true;
}

void Label::Draw() {
  if (buffer_)
    buffer_->Draw(GL_TRIANGLES);
}

} // namespace canvas
} // namespace lviz
