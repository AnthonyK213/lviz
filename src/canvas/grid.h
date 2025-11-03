#ifndef _LVIZ_CANVAS_GRID_H
#define _LVIZ_CANVAS_GRID_H

#include "../render/gl_vertex_buffer.h"
#include "../render/shader.h"
#include "presentable.h"

#include <memory>

namespace lviz {
namespace canvas {

class Camera;

class Grid : public Presentable {
public:
  Grid(Camera *camera);

  ~Grid();

  virtual Type GetType() const override;

  virtual gp::Box GetBox() const override;

  virtual bool CreateBuffers() override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> buffer_;
  std::unique_ptr<render::Shader> shader_;
  Camera *camera_;
};

} // namespace canvas
} // namespace lviz

#endif
