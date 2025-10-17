#ifndef _LVIZ_CANVAS_POLYLINE_H
#define _LVIZ_CANVAS_POLYLINE_H

#include "geometry.h"

#include "../render/gl_vertex_buffer.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace lviz {
namespace canvas {

class Polyline : public Geometry {
public:
  Polyline(std::vector<glm::vec3> &&vertices);

  ~Polyline();

  virtual void UpdateShader(render::Shader *shader) override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
  std::vector<glm::vec3> vertices_;
};

} // namespace canvas
} // namespace lviz

#endif
