#ifndef _LVIZ_RENDER_GL_VERTEX_ARRAY_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_ARRAY_BUFFER_H

#include "gl_vertex_buffer.h"

#include <glm/glm.hpp>

#include "../canvas/vertex.h"

namespace lviz {
namespace render {

class GLVertexArrayBuffer : public GLVertexBuffer {
public:
  GLVertexArrayBuffer(int n_vertices, const canvas::Vertex vertices[]);

  ~GLVertexArrayBuffer();

  virtual void Draw(GLenum mode) override;

private:
  void createBuffers(int n_vertices, const canvas::Vertex vertices[]);

  void deleteBuffers();

private:
  GLuint vbo_;
  GLuint vao_;
  int count_;
};

} // namespace render
} // namespace lviz

#endif
