#include "gl_vertex_index_buffer.h"

namespace lviz {
namespace render {

GLVertexIndexBuffer::GLVertexIndexBuffer(int n_vertices,
                                         const canvas::Vertex vertices[],
                                         int n_indices,
                                         const glm::u32 indices[])
    : GLVertexBuffer(), vbo_(0), vao_(0), ibo_(0), count_(0) {
  createBuffers(n_vertices, vertices, n_indices, indices);
}

GLVertexIndexBuffer::~GLVertexIndexBuffer() {
  deleteBuffers();
}

void GLVertexIndexBuffer::Draw(GLenum mode) {
  glBindVertexArray(vao_);
  glDrawElements(mode, count_, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

void GLVertexIndexBuffer::createBuffers(int n_vertices,
                                        const canvas::Vertex vertices[],
                                        int n_indices,
                                        const glm::u32 indices[]) {
  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &ibo_);
  glGenBuffers(1, &vbo_);

  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(canvas::Vertex), vertices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(glm::u32), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(canvas::Vertex),
                        (void *)offsetof(canvas::Vertex, normal));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  count_ = n_indices;
}

void GLVertexIndexBuffer::deleteBuffers() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ibo_);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

} // namespace render
} // namespace lviz
