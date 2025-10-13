#ifndef _LVIZ_UI_PANEL_H
#define _LVIZ_UI_PANEL_H

#include <string>

#include <imgui.h>

#include <ImFileBrowser.h>

namespace lviz {
namespace ui {

class Panel {
public:
  Panel();

  ~Panel();

  void Render();

private:
  ImGui::FileBrowser file_dialog_;
  std::string current_file_;
};

} // namespace ui
} // namespace lviz

#endif
