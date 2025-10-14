#ifndef _LVIZ_RENDER_GL_VERTEX_BUFFER_H
#define _LVIZ_RENDER_GL_VERTEX_BUFFER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <vector>

namespace lviz {
namespace render {

class GLVertexBuffer {
public:
  GLVertexBuffer();

  ~GLVertexBuffer();

  void CreateBuffers(const std::vector<glm::vec3> &vertices,
                     const std::vector<glm::u32> &indices);

  void DeleteBuffers();

  void Bind();

  void Unbind();

  void Draw(int index_count);

private:
  GLuint vbo_;
  GLuint vao_;
  GLuint ibo_;
};

} // namespace render
} // namespace lviz

#endif
