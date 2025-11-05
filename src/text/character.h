#ifndef _LVIZ_TEXT_CHARACTER_H
#define _LVIZ_TEXT_CHARACTER_H

#include <glm/glm.hpp>

namespace lviz {
namespace text {

struct Character {
  glm::vec2 top_left;
  glm::vec2 bot_right;
  glm::ivec2 size;
  glm::ivec2 bearing;
  glm::u32 advance;
};

} // namespace text
} // namespace lviz

#endif
