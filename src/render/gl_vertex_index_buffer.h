#ifndef _LVIZ_RENDER_GL_VERTEX_INDEX_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_INDEX_BUFFER_H

#include "gl_vertex_buffer.h"

#include <glm/glm.hpp>

#include "../canvas/vertex.h"

namespace lviz {
namespace render {

class GLVertexIndexBuffer : public GLVertexBuffer {
public:
  GLVertexIndexBuffer(int n_vertices, const canvas::Vertex vertices[],
                      int n_indices, const glm::u32 indices[]);

  ~GLVertexIndexBuffer();

  virtual void Draw(GLenum mode) override;

private:
  void createBuffers(int n_vertices, const canvas::Vertex vertices[],
                     int n_indices, const glm::u32 indices[]);

  void deleteBuffers();

private:
  GLuint vbo_;
  GLuint vao_;
  GLuint ibo_;
  int count_;
};

} // namespace render
} // namespace lviz

#endif
