#ifndef _LVIZ_APPL_APPLICATION_H
#define _LVIZ_APPL_APPLICATION_H

#include "../util/app_path.h"
#include "../window/gl_window.h"
#include "extension_manager.h"
#include "log_stream.h"
#include "state.h"

#include <memory>
#include <string>

namespace lviz {
namespace appl {

class Application {
public:
  Application();

  ~Application();

  State *GetState() const {
    return state_.get();
  }

  void Run();

private:
  std::unique_ptr<window::GLWindow> window_;
  std::unique_ptr<ExtensionManager> manager_;
  std::unique_ptr<LogStream> log_stream_;
  std::unique_ptr<State> state_;
};

} // namespace appl
} // namespace lviz

#endif
