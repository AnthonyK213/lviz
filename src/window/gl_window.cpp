#include "gl_window.h"

namespace lviz {
namespace window {

GLWindow::GLWindow() : window_(nullptr), running_(false) {
  ui_ctx_ = std::make_unique<render::UIContext>();
  gl_ctx_ = std::make_unique<render::GLContext>();
}

GLWindow::~GLWindow() {
  ui_ctx_->Close();
  gl_ctx_->Close();
}

bool GLWindow::Init(int width, int height, const std::string &titile) {
  width_ = width;
  height_ = height;
  title_ = titile;

  gl_ctx_->Init(this);
  ui_ctx_->Init(this);

  panel_ = std::make_unique<ui::Panel>();
  view3d_ = std::make_unique<ui::View3d>();

  running_ = true;

  return running_;
}

void GLWindow::Render() {
  gl_ctx_->PreRender();
  ui_ctx_->PreRender();

  panel_->Render();
  view3d_->Render();

  ui_ctx_->PostRender();
  gl_ctx_->PostRender();
}

void GLWindow::OnScroll(double delta) {}

void GLWindow::OnKey(int key, int scancode, int action, int mods) {}

void GLWindow::OnResize(int width, int height) {}

void GLWindow::OnClose() {
  running_ = false;
}

} // namespace window
} // namespace lviz
