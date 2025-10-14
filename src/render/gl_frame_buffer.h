#ifndef _LVIZ_RENDER_GL_FRAME_BUFFER_H
#define _LVIZ_RENDER_GL_FRAME_BUFFER_H

#include <glad/glad.h>

namespace lviz {
namespace render {

class GLFrameBuffer {
public:
  GLFrameBuffer();

  ~GLFrameBuffer();

  void CreateBuffers(int width, int height);

  void DeleteBuffers();

  void Bind();

  void Unbind();

  GLuint GetTexture() const {
    return tex_id_;
  }

private:
  GLuint fbo_;
  GLuint tex_id_;
  GLuint depth_id_;
  int width_;
  int height_;
};

} // namespace render
} // namespace lviz

#endif
