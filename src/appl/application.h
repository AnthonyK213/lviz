#ifndef _LVIZ_APPL_APPLICATION_H
#define _LVIZ_APPL_APPLICATION_H

#include <memory>
#include <string>

#include "../window/gl_window.h"

namespace lviz {
namespace appl {

class Application {
public:
  Application(const std::string &app_name);

  void Run();

private:
  std::unique_ptr<window::GLWindow> window_;
};

} // namespace appl
} // namespace lviz

#endif
