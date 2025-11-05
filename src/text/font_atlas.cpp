#include "font_atlas.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../util/scope_guard.h"

namespace lviz {
namespace text {

FontAtlas::FontAtlas()
    : char_map_(), tex_id_(0), tex_width_(0), tex_height_(0) {}

FontAtlas::~FontAtlas() {
  glDeleteTextures(1, &tex_id_);
}

bool FontAtlas::Init(const std::string &font) {
  FT_Library ft = nullptr;
  auto ft_guard = util::MakeScopeGuard([&]() { FT_Done_FreeType(ft); });
  if (FT_Init_FreeType(&ft)) {
    return false;
  }

  FT_Face face = nullptr;
  auto face_guard = util::MakeScopeGuard([&]() { FT_Done_Face(face); });
  if (FT_New_Face(ft, font.c_str(), 0, &face)) {
    return false;
  }

  char_map_.clear();
  glDeleteTextures(1, &tex_id_);
  tex_width_ = tex_height_ = 0;

  FT_Set_Pixel_Sizes(face, 0, 128);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; ++c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      continue;
    }

    tex_width_ += face->glyph->bitmap.width;
    tex_height_ = std::max(tex_height_, face->glyph->bitmap.rows);
  }

  glGenTextures(1, &tex_id_);
  glBindTexture(GL_TEXTURE_2D, tex_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, tex_width_, tex_height_, 0, GL_RED,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int x = 0;

  for (unsigned char c = 0; c < 128; ++c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      continue;
    }

    glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, face->glyph->bitmap.width,
                    face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer);

    Character ch;

    ch.size = glm::ivec2{face->glyph->bitmap.width, face->glyph->bitmap.rows};
    ch.bearing = glm::ivec2{face->glyph->bitmap_left, face->glyph->bitmap_top};
    ch.advance = face->glyph->advance.x;

    ch.top_left.x = (float)x / tex_width_;
    ch.top_left.y = 0.0f;
    ch.bot_right.x = (float)(x + ch.size.x) / tex_width_;
    ch.bot_right.y = (float)(ch.size.y) / tex_height_;

    char_map_.insert({c, ch});

    x += face->glyph->bitmap.width;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

void FontAtlas::Bind() const {
  glBindTexture(GL_TEXTURE_2D, tex_id_);
}

void FontAtlas::Unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace text
} // namespace lviz
