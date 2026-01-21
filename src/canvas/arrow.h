#ifndef _LVIZ_CANVAS_ARROW_H
#define _LVIZ_CANVAS_ARROW_H

#include "../gp/xyz.h"
#include "../render/gl_vertex_buffer.h"
#include "../render/gl_vertex_buffer_layout.h"
#include "presentable.h"
#include "vertex.h"

#include <vector>

namespace lviz {
namespace canvas {

class Arrow : public Presentable {
public:
  Arrow(const gp::Pnt &location, const gp::Vec &vector, glm::f32 tip_angle,
        glm::f32 tip_length, int n_fins);

  virtual Type GetType() const override;

  virtual gp::Box GetBox() const override;

  virtual bool CreateBuffers() override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> buffer_;
  std::vector<canvas::Vertex> vertices_;
  gp::Vec vec_;
  glm::f32 tip_ang_;
  glm::f32 tip_len_;
  int n_fins_;
};

} // namespace canvas
} // namespace lviz

#endif
