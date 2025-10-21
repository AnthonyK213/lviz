#include "gl_vertex_buffer.h"

namespace lviz {
namespace render {

GLVertexBuffer::GLVertexBuffer() : vbo_(0), vao_(0) {}

GLVertexBuffer::~GLVertexBuffer() {
  DeleteBuffers();
}

void GLVertexBuffer::CreateBuffers(int n_vertices,
                                   const canvas::Vertex vertices[]) {
  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &vbo_);

  Bind();

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(canvas::Vertex), vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)offsetof(canvas::Vertex, normal));
  glEnableVertexAttribArray(1);

  Unbind();
}

void GLVertexBuffer::DeleteBuffers() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

void GLVertexBuffer::Bind() {
  glBindVertexArray(vao_);
}

void GLVertexBuffer::Unbind() {
  glBindVertexArray(0);
}

void GLVertexBuffer::Draw(GLenum mode, int index_count) {
  Bind();

  glDrawArrays(mode, 0, index_count);

  Unbind();
}

} // namespace render
} // namespace lviz
