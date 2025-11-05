#ifndef _LVIZ_TEXT_FONT_ATLAS_H
#define _LVIZ_TEXT_FONT_ATLAS_H

#include <glad/glad.h>

#include "character.h"

#include <map>
#include <string>

namespace lviz {
namespace text {

class FontAtlas {
public:
  FontAtlas();

  ~FontAtlas();

  bool Init(const std::string &font);

  const Character *GetCharacter(char c) const;

  GLuint GetWidth() const {
    return tex_width_;
  }

  GLuint GetHeight() const {
    return tex_height_;
  }

  void Bind() const;

  void Unbind() const;

private:
  std::map<char, Character> char_map_;
  GLuint tex_id_;
  GLuint tex_width_;
  GLuint tex_height_;
};

} // namespace text
} // namespace lviz

#endif
