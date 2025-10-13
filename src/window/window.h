#ifndef _LVIZ_WINDOW_WINDOW_H
#define _LVIZ_WINDOW_WINDOW_H

#include <string>

namespace lviz {
namespace window {

class Window {
public:
  virtual ~Window();

  const std::string &GetTitle() const {
    return title_;
  }

  void GetTitle(const std::string &title) {
    title_ = title;
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
  std::string title_;
  int width_;
  int height_;
};

} // namespace window
} // namespace lviz

#endif
