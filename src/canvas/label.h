#ifndef _LVIZ_CANVAS_LABEL_H
#define _LVIZ_CANVAS_LABEL_H

#include "../gp/xyz.h"
#include "presentable.h"

#include <string>

namespace lviz {
namespace canvas {

class Label : public Presentable {
public:
  Label(const std::string &text, const gp::Pnt &location, int size);

  const std::string &GetText() const {
    return txt_;
  }

  const gp::Pnt &GetLocation() const {
    return loc_;
  }

  const int GetSize() const {
    return size_;
  }

  virtual Type GetType() const override;

  virtual gp::Box GetBox() const override;

  virtual bool CreateBuffers() override;

  virtual void Draw() override;

private:
  std::string txt_;
  gp::Pnt loc_;
  int size_;
};

} // namespace canvas
} // namespace lviz

#endif
