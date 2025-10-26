#ifndef _LVIZ_CANVAS_TRIANGLE_H
#define _LVIZ_CANVAS_TRIANGLE_H

#include "surface.h"
#include "vertex.h"

#include <glm/glm.hpp>

#include <memory>

namespace lviz {
namespace canvas {

class Triangle : public Surface {
public:
  Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
           const glm::vec3 &point3);

  Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
           const glm::vec3 &point3, const glm::vec3 &normal1,
           const glm::vec3 &normal2, const glm::vec3 &normal3);

private:
  Vertex vertices_[3];
};

} // namespace canvas
} // namespace lviz

#endif
