#ifndef _LVIZ_WINDOW_GL_WINDOW_H
#define _LVIZ_WINDOW_GL_WINDOW_H

#include <GLFW/glfw3.h>

#include <memory>

#include "window.h"

#include "../context/gl_context.h"
#include "../context/ui_context.h"

#include "../ui/panel.h"
#include "../ui/view3d.h"

namespace lviz {
namespace window {

class GLWindow : public Window {
public:
  GLWindow();

  ~GLWindow();

  bool Init(int width, int height, const std::string &titile);

  bool IsRunning() const {
    return running_;
  }

  void Render();

  virtual void *GetNativeWindow() const override {
    return window_;
  }

  virtual void SetNativeWindow(void *win) override {
    window_ = (GLFWwindow *)win;
  }

  virtual void OnScroll(double delta) override;

  virtual void OnKey(int key, int scancode, int action, int mods) override;

  virtual void OnResize(int width, int height) override;

  virtual void OnClose() override;

private:
  GLFWwindow *window_;
  std::unique_ptr<context::UIContext> ui_ctx_;
  std::unique_ptr<context::GLContext> gl_ctx_;
  std::unique_ptr<ui::Panel> panel_;
  std::unique_ptr<ui::View3d> view3d_;
  bool running_;
};

} // namespace window
} // namespace lviz

#endif
