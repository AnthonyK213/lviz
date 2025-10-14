#include "gl_frame_buffer.h"

namespace lviz {
namespace render {

GLFrameBuffer::GLFrameBuffer()
    : fbo_(0), tex_id_(0), depth_id_(0), width_(0), height_(0) {}

GLFrameBuffer::~GLFrameBuffer() {
  DeleteBuffers();
}

void GLFrameBuffer::CreateBuffers(int width, int height) {
  width_ = width;
  height_ = height;

  if (fbo_) {
    DeleteBuffers();
  }

  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glCreateTextures(GL_TEXTURE_2D, 1, &tex_id_);
  glBindTexture(GL_TEXTURE_2D, tex_id_);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         tex_id_, 0);

  glCreateTextures(GL_TEXTURE_2D, 1, &depth_id_);
  glBindTexture(GL_TEXTURE_2D, depth_id_);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width_, height_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D, depth_id_, 0);

  GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(tex_id_, buffers);

  Unbind();
}

void GLFrameBuffer::DeleteBuffers() {
  if (fbo_) {
    glDeleteFramebuffers(GL_FRAMEBUFFER, &fbo_);
    glDeleteTextures(1, &tex_id_);
    glDeleteTextures(1, &depth_id_);
    tex_id_ = 0;
    depth_id_ = 0;
  }
}

void GLFrameBuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glViewport(0, 0, width_, height_);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFrameBuffer::Unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace render
} // namespace lviz
