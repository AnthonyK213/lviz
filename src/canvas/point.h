#ifndef _LVIZ_CANVAS_POINT_H
#define _LVIZ_CANVAS_POINT_H

#include "geometry.h"
#include "vertex.h"

#include "../gp/glm.h"
#include "../render/gl_vertex_buffer.h"

#include <memory>

namespace lviz {
namespace canvas {

class Point : public Geometry {
public:
  Point(const gp::Pnt &coord);

  virtual void UpdateShader(render::Shader *shader) override;

  virtual bool CreateBuffers() override;

  virtual GeomType GetType() const override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
  Vertex vertex_;
};

} // namespace canvas
} // namespace lviz

#endif
