#ifndef _LVIZ_RENDER_UI_CONTEXT_H
#define _LVIZ_RENDER_UI_CONTEXT_H

#include "context.h"

namespace lviz {
namespace render {

class UIContext : public Context {
public:
  UIContext();

  virtual bool Init(window::Window *win) override;

  virtual void PreRender() override;

  virtual void PostRender() override;

  virtual void Close() override;
};

} // namespace render
} // namespace lviz

#endif
