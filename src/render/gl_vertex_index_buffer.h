#ifndef _LVIZ_RENDER_GL_VERTEX_INDEX_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_INDEX_BUFFER_H

#include "gl_vertex_buffer.h"
#include "gl_vertex_buffer_layout.h"

namespace lviz {
namespace render {

template <typename Vertex_, typename Layout_ = Vertex_>
class GLVertexIndexBuffer : public GLVertexBuffer {
public:
  GLVertexIndexBuffer(int n_vertices, const Vertex_ vertices[], int n_indices,
                      const GLuint indices[])
      : GLVertexBuffer(), vbo_(0), vao_(0), ibo_(0), count_(0) {
    glGenVertexArrays(1, &vao_);

    glGenBuffers(1, &ibo_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(Vertex_), vertices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(GLuint), indices,
                 GL_STATIC_DRAW);

    const GLVertexBufferLayout &layout = Layout_::GetLayout();
    for (int i = 0; i < layout.size(); ++i) {
      const GLVertexBufferElement &elem = layout[i];
      glVertexAttribPointer(i, elem.count, elem.type, GL_FALSE, sizeof(Vertex_),
                            (void *)elem.offset);
      glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);

    count_ = n_indices;
  }

  ~GLVertexIndexBuffer() {
    const GLVertexBufferLayout &layout = Layout_::GetLayout();
    for (int i = 0; i < layout.size(); ++i) {
      glDisableVertexAttribArray(i);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ibo_);
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
  }

  virtual void Draw(GLenum mode) override {
    glBindVertexArray(vao_);
    glDrawElements(mode, count_, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }

private:
  GLuint vbo_;
  GLuint vao_;
  GLuint ibo_;
  int count_;
};

} // namespace render
} // namespace lviz

#endif
