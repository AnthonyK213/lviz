#ifndef _LVIZ_CONTEXT_CONTEXT_H
#define _LVIZ_CONTEXT_CONTEXT_H

namespace lviz {
namespace window {

class Window;

} // namespace window

namespace context {

class Context {
public:
  virtual ~Context();

  virtual bool Init(window::Window *win);

  virtual void PreRender() = 0;

  virtual void PostRender() = 0;

  virtual void Close() = 0;

protected:
  Context();

protected:
  window::Window *window_;
};

} // namespace context
} // namespace lviz

#endif
