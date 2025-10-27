#ifndef _LVIZ_CANVAS_VERTEX_H
#define _LVIZ_CANVAS_VERTEX_H

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

struct Vertex {
  glm::vec3 coord;
  glm::vec3 normal;

  Vertex() : coord(), normal() {}

  Vertex(const glm::vec3 &coord) : coord(coord), normal() {}

  Vertex(const glm::vec3 &coord, const glm::vec3 &normal)
      : coord(coord), normal(normal) {}
};

} // namespace canvas
} // namespace lviz

#endif
