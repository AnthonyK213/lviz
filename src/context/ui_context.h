#ifndef _LVIZ_CONTEXT_UI_CONTEXT_H
#define _LVIZ_CONTEXT_UI_CONTEXT_H

#include "context.h"

namespace lviz {
namespace context {

class UIContext : public Context {
public:
  UIContext();

  virtual bool Init(window::Window *win) override;

  virtual void PreRender() override;

  virtual void PostRender() override;

  virtual void Close() override;
};

} // namespace context
} // namespace lviz

#endif
