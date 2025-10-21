#ifndef _LVIZ_CANVAS_GRID_H
#define _LVIZ_CANVAS_GRID_H

#include "../render/gl_vertex_index_buffer.h"
#include "../render/shader.h"

#include <memory>

namespace lviz {
namespace canvas {

class Camera;

class Grid {
public:
  Grid();

  ~Grid();

  void Draw(Camera *camera);

private:
  std::unique_ptr<render::Shader> shader_;
  GLuint vbo_;
  GLuint vao_;
  GLuint ibo_;
};

} // namespace canvas
} // namespace lviz

#endif
