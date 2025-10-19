#ifndef _LVIZ_WINDOW_WINDOW_H
#define _LVIZ_WINDOW_WINDOW_H

#include <string>

namespace lviz {
namespace appl {

class Application;

} // namespace appl

namespace window {

class Window {
public:
  virtual ~Window() = default;

  appl::Application *GetApp() const {
    return app_;
  }

  const std::string &GetTitle() const {
    return title_;
  }

  int GetWidth() const {
    return width_;
  }

  int GetHeight() const {
    return height_;
  }

  virtual void *GetNativeWindow() const = 0;

  virtual void SetNativeWindow(void *win) = 0;

  virtual void OnScroll(double delta) = 0;

  virtual void OnKey(int key, int scancode, int action, int mods) = 0;

  virtual void OnResize(int width, int height) = 0;

  virtual void OnClose() = 0;

protected:
  Window(appl::Application *app) : app_(app), title_(), width_(0), height_(0) {}

protected:
  appl::Application *app_;
  std::string title_;
  int width_;
  int height_;
};

} // namespace window
} // namespace lviz

#endif
