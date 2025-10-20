#ifndef _LVIZ_UI_VIEW3D_H
#define _LVIZ_UI_VIEW3D_H

#include <glm/glm.hpp>

#include "../canvas/camera.h"
#include "../canvas/geometry.h"
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

  void Render();

  void Purge();

  bool DrawPoint(const glm::vec3 &point);

  bool DrawLine(const glm::vec3 &point1, const glm::vec3 &point2);

  bool DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                    const glm::vec3 &point3);

  bool DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                    const glm::vec3 &point3, const glm::vec3 &normal1,
                    const glm::vec3 &normal2, const glm::vec3 &normal3);

  void Resize(int width, int height);

  void OnMouseMove(double x, double y, ui::MouseButton button);

  void OnMouseWheel(double delta);

private:
  window::Window *parent_;
  std::unique_ptr<canvas::Camera> camera_;
  std::unique_ptr<canvas::Light> light_;
  std::unique_ptr<render::GLFrameBuffer> frame_buffer_;
  std::unique_ptr<render::Shader> shader_;
  std::vector<std::unique_ptr<canvas::Geometry>> geometries_;
  glm::vec2 size_;
  glm::vec2 cursor_;
};

} // namespace ui
} // namespace lviz

#endif
