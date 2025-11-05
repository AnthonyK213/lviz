#include "label.h"

namespace lviz {
namespace canvas {

Label::Label(const std::string &text, const gp::Pnt &location, int size)
    : txt_(text), loc_(location), size_(size) {}

Presentable::Type Label::GetType() const {
  return Type::Label;
}

gp::Box Label::GetBox() const {
  return gp::Box();
}

bool Label::CreateBuffers() {
  return true;
}

void Label::Draw() {}

} // namespace canvas
} // namespace lviz
