#ifndef _LVIZ_UI_PANEL_H
#define _LVIZ_UI_PANEL_H

#include <string>

#include <imgui.h>

#include <imfilebrowser.h>

namespace lviz {
namespace window {

class Window;

}

namespace ui {

class Panel {
public:
  Panel(window::Window *parent);

  ~Panel();

  void Setup();

  void Render();

private:
  void setupProjection();

  void setupScale();

  void setupShowGrid();

private:
  window::Window *parent_;
  ImGui::FileBrowser file_dialog_;
  std::string current_file_;
  int current_proj_idx_;
  int current_scale_idx_;
  bool show_grid_;
};

} // namespace ui
} // namespace lviz

#endif
