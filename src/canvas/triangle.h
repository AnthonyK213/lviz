#ifndef _LVIZ_CANVAS_TRIANGLE_H
#define _LVIZ_CANVAS_TRIANGLE_H

#include "geometry.h"

#include "../render/gl_vertex_buffer.h"

#include <memory>

namespace lviz {
namespace canvas {

class Triangle : public Geometry {
public:
  Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
           const glm::vec3 &point3);

  Triangle(const glm::vec3 &point1, const glm::vec3 &point2,
           const glm::vec3 &point3, const glm::vec3 &normal1,
           const glm::vec3 &normal2, const glm::vec3 &normal3);

  ~Triangle();

  virtual void UpdateShader(render::Shader *shader) override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
  Vertex vertices_[3];
};

} // namespace canvas
} // namespace lviz

#endif
