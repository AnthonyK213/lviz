#ifndef _LVIZ_UI_PANEL_H
#define _LVIZ_UI_PANEL_H

#include <string>

#include <imgui.h>

#include <ImFileBrowser.h>

namespace lviz {
namespace window {

class Window;

}

namespace ui {

class Panel {
public:
  Panel(window::Window *parent);

  ~Panel();

  void Render();

private:
  window::Window *parent_;
  ImGui::FileBrowser file_dialog_;
  std::string current_file_;
};

} // namespace ui
} // namespace lviz

#endif
