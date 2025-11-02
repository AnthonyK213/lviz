#ifndef _LVIZ_RENDER_GL_BUFFER_ELEMENT_H
#define _LVIZ_RENDER_GL_BUFFER_ELEMENT_H

#include <glad/glad.h>

#include <vector>

namespace lviz {
namespace render {

struct GLVertexBufferElement {
  std::size_t offset;
  GLuint type;
  GLuint count;

  GLVertexBufferElement() : type(GL_NONE), count(0), offset(0) {}

  GLVertexBufferElement(GLuint type, GLuint count, std::size_t offset)
      : type(type), count(count), offset(offset) {}
};

using GLVertexBufferLayout = std::vector<GLVertexBufferElement>;

} // namespace render
} // namespace lviz

#endif
