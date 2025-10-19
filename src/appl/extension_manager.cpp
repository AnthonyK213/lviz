#include "extension_manager.h"

namespace lviz {
namespace appl {

ExtensionManager::ExtensionManager(const std::filesystem::path &ext_dir,
                                   Application *app)
    : ext_dir_(ext_dir), app_(app) {}

bool ExtensionManager::Init() {
  if (!std::filesystem::is_directory(ext_dir_))
    return false;

  for (const auto &entry : std::filesystem::directory_iterator(ext_dir_)) {
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
