#ifndef _LVIZ_UI_VIEW3D_H
#define _LVIZ_UI_VIEW3D_H

#include <glm/glm.hpp>

#include "../canvas/camera.h"
#include "../canvas/geometry.h"
#include "../canvas/grid.h"
#include "../canvas/handle.h"
#include "../canvas/light.h"
#include "../render/gl_frame_buffer.h"
#include "../render/shader.h"
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

  void Purge();

  bool AddGeometry(const canvas::handle<canvas::Geometry> &geom);

  void Resize(int width, int height);

  void OnMouseMove(double x, double y, ui::MouseButton button);

  void OnMouseWheel(double delta);

private:
  window::Window *parent_;
  std::unique_ptr<canvas::Camera> camera_;
  std::unique_ptr<canvas::Light> light_;
  std::unique_ptr<render::GLFrameBuffer> frame_buffer_;
  std::unique_ptr<render::Shader> shader_;
  std::unique_ptr<canvas::Grid> grid_;
  std::vector<canvas::handle<canvas::Geometry>> geometries_;
  glm::vec2 size_;
  glm::vec2 cursor_;
};

} // namespace ui
} // namespace lviz

#endif
