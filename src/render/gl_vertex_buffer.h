#ifndef _LVIZ_RENDER_GL_VERTEX_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_BUFFER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace lviz {
namespace render {

class GLVertexBuffer {
public:
  GLVertexBuffer();

  ~GLVertexBuffer();

  void CreateBuffers(int n_vertices, const glm::vec3 vertices[]);

  void DeleteBuffers();

  void Bind();

  void Unbind();

  void Draw(GLenum mode, int index_count);

private:
  GLuint vbo_;
  GLuint vao_;
};

} // namespace render
} // namespace lviz

#endif
