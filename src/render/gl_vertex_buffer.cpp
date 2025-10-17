#include "gl_vertex_buffer.h"

namespace lviz {
namespace render {

GLVertexBuffer::GLVertexBuffer() : vbo_(0), vao_(0) {}

GLVertexBuffer::~GLVertexBuffer() {
  DeleteBuffers();
}

void GLVertexBuffer::CreateBuffers(const std::vector<glm::vec3> &vertices) {
  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &vbo_);

  Bind();

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(0);

  Unbind();
}

void GLVertexBuffer::DeleteBuffers() {
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
