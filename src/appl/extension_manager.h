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
  explicit ExtensionManager(Application *app);

  Application *GetApp() const {
    return app_;
  }

  const std::list<Extension> &GetExtensions() const {
    return exts_;
  }

  bool Init(const std::filesystem::path &dir);

  bool Load();

private:
  Application *app_;
  std::list<Extension> exts_;
};

} // namespace appl

} // namespace lviz

#endif
