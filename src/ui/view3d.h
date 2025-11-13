#ifndef _LVIZ_UI_VIEW3D_H
#define _LVIZ_UI_VIEW3D_H

#include <glm/glm.hpp>

#include "../canvas/camera.h"
#include "../canvas/grid.h"
#include "../canvas/handle.h"
#include "../canvas/label.h"
#include "../canvas/light.h"
#include "../canvas/presentable.h"
#include "../render/shader.h"
#include "../text/font_atlas.h"
#include "input.h"

#include <memory>
#include <vector>

namespace lviz {
namespace window {

class Window;

}

namespace ui {

class View3d {
public:
  View3d(window::Window *parent,
         const glm::vec2 &init_size = glm::vec2{800.0f, 600.0f});

  ~View3d();

  canvas::Camera *GetCamera() const {
    return camera_.get();
  }

  void Render();

  void Clear();

  bool Display(const canvas::handle<canvas::Presentable> &obj);

  void ZoomAll();

  void Resize(int width, int height);

  void SetScale(glm::f32 scale);

  void SetShowGrid(bool show_grid);

  void OnMouseMove(double x, double y, ui::MouseButton button);

  void OnMouseWheel(double delta);

private:
  window::Window *parent_;
  std::unique_ptr<canvas::Camera> camera_;
  std::unique_ptr<canvas::Light> light_;
  std::unique_ptr<render::Shader> pnt_shader_;
  std::unique_ptr<render::Shader> crv_shader_;
  std::unique_ptr<render::Shader> srf_shader_;
  std::unique_ptr<render::Shader> lbl_shader_;
  std::unique_ptr<canvas::Grid> grid_;
  std::unique_ptr<text::FontAtlas> font_atlas_;
  std::vector<canvas::handle<canvas::Presentable>> points_;
  std::vector<canvas::handle<canvas::Presentable>> curves_;
  std::vector<canvas::handle<canvas::Presentable>> surfaces_;
  std::vector<canvas::handle<canvas::Label>> labels_;
  glm::vec2 size_;
  glm::vec2 cursor_;
  glm::f32 pnt_size_;
  glm::f32 crv_width_;
  glm::f32 scale_;
  bool show_grid_;
};

} // namespace ui
} // namespace lviz

#endif
