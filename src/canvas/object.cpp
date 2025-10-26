#include "object.h"

namespace lviz {
namespace canvas {

Object::Object() : rc_(0) {}

Object::Object(const Object &) : rc_(0) {}

Object &Object::operator=(const Object &) {
  return *this;
}

Object::~Object() {}

Object *Object::This() const {
  if (GetRefCount() == 0)
    return nullptr;
  return const_cast<Object *>(this);
}

} // namespace canvas
} // namespace lviz
