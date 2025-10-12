#include "application.h"
#include "../ui/frame.h"

namespace lviz::app {

Application::Application() {}

bool Application::OnInit() {
  if (!wxApp::OnInit())
    return false;

  ui::Frame *frame = new ui::Frame("Lviz", wxDefaultPosition, {960, 720});
  frame->Show(true);

  return true;
}

} // namespace lviz::app
