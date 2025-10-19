#ifndef _LVIZ_APPL_EXTENSION_MANAGER_H
#define _LVIZ_APPL_EXTENSION_MANAGER_H

#include <filesystem>
#include <list>
#include <string>

#include "extension.h"

namespace lviz {
namespace appl {

class Application;

class ExtensionManager {
public:
  explicit ExtensionManager(const std::filesystem::path &ext_dir,
                            Application *app);

  Application *GetApp() const {
    return app_;
  }

  bool Init();

  bool Load();

private:
  std::filesystem::path ext_dir_;
  Application *app_;
  std::list<Extension> exts_;
};

} // namespace appl

} // namespace lviz

#endif
