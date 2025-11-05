#ifndef _LVIZ_CANVAS_LABEL_H
#define _LVIZ_CANVAS_LABEL_H

#include "../gp/xyz.h"
#include "../render/gl_vertex_buffer.h"
#include "../render/gl_vertex_buffer_layout.h"
#include "../text/font_atlas.h"
#include "presentable.h"

#include <memory>
#include <string>
#include <vector>

namespace lviz {
namespace canvas {

struct LabelVertex {
  glm::vec2 coord;
  glm::vec2 uv;

  LabelVertex(const glm::vec2 &coord, const glm::vec2 &uv);

  static const render::GLVertexBufferLayout &GetLayout();
};

class Label : public Presentable {
public:
  Label(const std::string &text, const gp::Pnt &location, glm::f32 size);

  const std::string &GetText() const {
    return txt_;
  }

  const gp::Pnt &GetLocation() const {
    return loc_;
  }

  const glm::f32 GetSize() const {
    return size_;
  }

  void BuildGlyphs(const text::FontAtlas *font_atlas);

  virtual Type GetType() const override;

  virtual gp::Box GetBox() const override;

  virtual bool CreateBuffers() override;

  virtual void Draw() override;

private:
  std::unique_ptr<render::GLVertexBuffer> buffer_;
  std::vector<LabelVertex> vertices_;
  std::string txt_;
  gp::Pnt loc_;
  glm::f32 size_;
};

} // namespace canvas
} // namespace lviz

#endif
