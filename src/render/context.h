#ifndef _LVIZ_RENDER_CONTEXT_H
#define _LVIZ_RENDER_CONTEXT_H

namespace lviz {
namespace window {

class Window;

} // namespace window

namespace render {

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

} // namespace render
} // namespace lviz

#endif
