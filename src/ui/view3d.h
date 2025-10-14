#ifndef _LVIZ_UI_VIEW3D_H
#define _LVIZ_UI_VIEW3D_H

#include <glm/glm.hpp>

#include "../canvas/camera.h"
#include "../render/gl_frame_buffer.h"
#include "../render/gl_vertex_buffer.h"
#include "../render/shader.h"
#include "input.h"

#include <memory>
#include <vector>

namespace lviz {
namespace ui {

class View3d {
public:
  View3d();

  ~View3d();

  void Render();

  void Purge();

  bool DrawPoint(const glm::vec3 &point);

  bool DrawLineSegment(const glm::vec3 &point1, const glm::vec3 &point2);

  bool DrawTriangle(const glm::vec3 &point1, const glm::vec3 &point2,
                    const glm::vec3 &point3);

  void Resize(int width, int height);

  void OnMouseMove(double x, double y, ui::MouseButton button);

  void OnMouseWheel(double delta);

private:
  std::unique_ptr<canvas::Camera> camera_;
  std::unique_ptr<render::GLFrameBuffer> frame_buffer_;
  std::unique_ptr<render::GLVertexBuffer> vertex_buffer_;
  std::unique_ptr<render::Shader> shader_;
  std::vector<glm::vec3> vertices_;
  std::vector<glm::u32> indices_;
  glm::vec2 size_;
  glm::vec2 cursor_;
};

} // namespace ui
} // namespace lviz

#endif
