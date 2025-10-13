#ifndef _LVIZ_CONTEXT_GL_CONTEXT_H
#define _LVIZ_CONTEXT_GL_CONTEXT_H

#include "context.h"

namespace lviz {
namespace context {

class GLContext : public Context {
public:
  GLContext();

  virtual bool Init(window::Window *win) override;

  virtual void PreRender() override;

  virtual void PostRender() override;

  virtual void Close() override;
};

} // namespace context
} // namespace lviz

#endif
