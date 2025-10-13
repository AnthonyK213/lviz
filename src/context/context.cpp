#include "context.h"

#include "../window/window.h"

namespace lviz {
namespace context {

Context::Context() : window_(nullptr) {}

Context::~Context() {}

bool Context::Init(window::Window *win) {
  window_ = win;
  return true;
}

} // namespace context

} // namespace lviz
