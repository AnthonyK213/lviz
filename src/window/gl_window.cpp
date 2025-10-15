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

void GLWindow::WaitEvents() const {
  glfwWaitEvents();
}

void GLWindow::OnScroll(double delta) {
  view3d_->OnMouseWheel(delta);
}

void GLWindow::OnKey(int key, int scancode, int action, int mods) {}

void GLWindow::OnResize(int width, int height) {
  width_ = width;
  height_ = height;

  view3d_->Resize(width_, height_);

  Render();
}

void GLWindow::OnClose() {
  running_ = false;
}

void GLWindow::HandleInput() {
  double x, y;
  glfwGetCursorPos(window_, &x, &y);

  ui::MouseButton button = ui::MouseButton::None;

  if (glfwGetMouseButton(window_, 0) == GLFW_PRESS)
    button = ui::MouseButton::Left;
  else if (glfwGetMouseButton(window_, 1) == GLFW_PRESS)
    button = ui::MouseButton::Right;
  else if (glfwGetMouseButton(window_, 2) == GLFW_PRESS)
    button = ui::MouseButton::Middle;

  view3d_->OnMouseMove(x, y, button);
}

} // namespace window
} // namespace lviz
