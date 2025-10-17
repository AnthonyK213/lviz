#include "gl_vertex_index_buffer.h"

namespace lviz {
namespace render {

GLVertexIndexBuffer::GLVertexIndexBuffer() : vbo_(0), vao_(0), ibo_(0) {}

GLVertexIndexBuffer::~GLVertexIndexBuffer() {
  DeleteBuffers();
}

void GLVertexIndexBuffer::CreateBuffers(const std::vector<glm::vec3> &vertices,
                                        const std::vector<glm::u32> &indices) {
  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &ibo_);
  glGenBuffers(1, &vbo_);

  Bind();

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::u32),
               indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(0);

  Unbind();
}

void GLVertexIndexBuffer::DeleteBuffers() {
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ibo_);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

void GLVertexIndexBuffer::Bind() {
  glBindVertexArray(vao_);
}

void GLVertexIndexBuffer::Unbind() {
  glBindVertexArray(0);
}

void GLVertexIndexBuffer::Draw(GLenum mode, int index_count) {
  Bind();

  glDrawElements(mode, index_count, GL_UNSIGNED_INT, nullptr);

  Unbind();
}

} // namespace render
} // namespace lviz
