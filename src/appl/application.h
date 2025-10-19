#ifndef _LVIZ_APPL_APPLICATION_H
#define _LVIZ_APPL_APPLICATION_H

#include <memory>
#include <string>

#include "../window/gl_window.h"
#include "extension_manager.h"
#include "state.h"

namespace lviz {
namespace appl {

class Application {
public:
  Application(const std::string &app_name);

  State *GetState() const {
    return state_.get();
  }

  void Run();

private:
  std::unique_ptr<window::GLWindow> window_;
  std::unique_ptr<ExtensionManager> manager_;
  std::unique_ptr<State> state_;
};

} // namespace appl
} // namespace lviz

#endif
