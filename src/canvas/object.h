#ifndef _LVIZ_CANVAS_OBJECT_H
#define _LVIZ_CANVAS_OBJECT_H

#include "../render/shader.h"

#include <atomic>

namespace lviz {
namespace canvas {

class Object {
public:
  Object();

  Object(const Object &);

  Object &operator=(const Object &);

  virtual ~Object();

  Object *This() const;

  inline int GetRefCount() const noexcept {
    return rc_;
  }

  inline void IncrementRefCounter() noexcept {
    ++rc_;
  }

  inline int DecrementRefCounter() noexcept {
    return --rc_;
  }

  virtual void Delete() const {
    delete this;
  }

  virtual void UpdateShader(render::Shader *shader) = 0;

private:
  std::atomic<int> rc_;
};

} // namespace canvas
} // namespace lviz

#endif
