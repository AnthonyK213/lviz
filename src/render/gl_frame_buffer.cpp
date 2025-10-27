#include "gl_frame_buffer.h"

#include <iostream>

namespace lviz {
namespace render {

GLFrameBuffer::GLFrameBuffer()
    : fbo_(0), tex_id_(0), depth_id_(0), width_(0), height_(0) {}

GLFrameBuffer::~GLFrameBuffer() {
  deleteBuffers();
}

void GLFrameBuffer::CreateBuffers(int width, int height) {
  width_ = width;
  height_ = height;

  if (!fbo_)
    glGenFramebuffers(1, &fbo_);

  glDeleteTextures(1, &tex_id_);
  glDeleteRenderbuffers(1, &depth_id_);
  tex_id_ = depth_id_ = 0;

  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  glGenTextures(1, &tex_id_);
  glBindTexture(GL_TEXTURE_2D, tex_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         tex_id_, 0);

  glGenRenderbuffers(1, &depth_id_);
  glBindRenderbuffer(GL_RENDERBUFFER, depth_id_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, depth_id_);

#ifndef NDEBUG
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!"
              << std::endl;
#endif

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glViewport(0, 0, width_, height_);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFrameBuffer::Unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::deleteBuffers() {
  if (fbo_) {
#ifndef NDEBUG
    if (glIsFramebuffer(fbo_) == GL_TRUE) {
      glDeleteFramebuffers(1, &fbo_);
      fbo_ = 0;
    } else {
      std::cerr << "WARN:: Frame buffer is invalid!" << std::endl;
    }

    if (glIsTexture(tex_id_) == GL_TRUE) {
      glDeleteTextures(1, &tex_id_);
      tex_id_ = 0;
    } else {
      std::cerr << "WARN:: Texture is invalid!" << std::endl;
    }

    if (glIsRenderbuffer(depth_id_) == GL_TRUE) {
      glDeleteRenderbuffers(1, &depth_id_);
      depth_id_ = 0;
    } else {
      std::cerr << "WARN:: Render buffer is invalid!" << std::endl;
    }
#else
    glDeleteFramebuffers(1, &fbo_);
    glDeleteTextures(1, &tex_id_);
    glDeleteRenderbuffers(1, &depth_id_);
    fbo_ = 0;
    tex_id_ = 0;
    depth_id_ = 0;
#endif
  }
}

} // namespace render
} // namespace lviz
