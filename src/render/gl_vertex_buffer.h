#ifndef _LVIZ_RENDER_GL_VERTEX_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_BUFFER_H

#include <glad/glad.h>

namespace lviz {
namespace render {

class GLVertexBuffer {
public:
  virtual ~GLVertexBuffer() = default;

  virtual void Draw(GLenum mode) = 0;

protected:
  GLVertexBuffer() = default;
};

} // namespace render
} // namespace lviz

#endif
