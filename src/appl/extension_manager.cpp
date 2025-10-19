#include "extension_manager.h"

namespace lviz {
namespace appl {

ExtensionManager::ExtensionManager(Application *app) : app_(app), exts_() {}

bool ExtensionManager::Init(const std::filesystem::path &dir) {
  if (!std::filesystem::is_directory(dir))
    return false;

  for (const auto &entry : std::filesystem::directory_iterator(dir)) {
    if (entry.is_directory()) {
      exts_.emplace_back(entry.path());
    }
  }

  return true;
}

bool ExtensionManager::Load() {
  for (Extension &ext : exts_) {
    ext.Load(this);
  }

  return true;
}

} // namespace appl
} // namespace lviz
