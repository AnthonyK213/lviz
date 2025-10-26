#include "gl_vertex_array_buffer.h"

namespace lviz {
namespace render {

GLVertexArrayBuffer::GLVertexArrayBuffer(int n_vertices,
                                         const canvas::Vertex vertices[])
    : GLVertexBuffer(), vbo_(0), vao_(0), count_(0) {
  createBuffers(n_vertices, vertices);
}

GLVertexArrayBuffer::~GLVertexArrayBuffer() {
  deleteBuffers();
}

void GLVertexArrayBuffer::Draw(GLenum mode) {
  glBindVertexArray(vao_);
  glDrawArrays(mode, 0, count_);
  glBindVertexArray(0);
}

void GLVertexArrayBuffer::createBuffers(int n_vertices,
                                        const canvas::Vertex vertices[]) {
  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &vbo_);

  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(canvas::Vertex), vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)offsetof(canvas::Vertex, normal));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  count_ = n_vertices;
}

void GLVertexArrayBuffer::deleteBuffers() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

} // namespace render
} // namespace lviz
