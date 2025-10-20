#ifndef _LVIZ_CANVAS_VERTEX_H
#define _LVIZ_CANVAS_VERTEX_H

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

struct Vertex {
  glm::vec3 coord;
  glm::vec3 normal;
};

} // namespace canvas
} // namespace lviz

#endif
