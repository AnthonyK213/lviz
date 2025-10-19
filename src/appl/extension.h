#ifndef _LVIZ_APPL_EXTENSION_H
#define _LVIZ_APPL_EXTENSION_H

#include <filesystem>
#include <string>

namespace lviz {
namespace appl {

class ExtensionManager;

class Extension {
public:
  enum class Type {
    None = 0,
    Executable,
    Library,
  };

public:
  explicit Extension(const std::filesystem::path &dir);

  bool IsValid() const {
    return type_ != Type::None;
  }

  bool IsLoaded() const {
    return loaded_;
  }

  std::string GetPath() const {
    return dir_.string();
  }

  std::string GetName() const {
    return dir_.filename().string();
  }

  void Load(ExtensionManager *manager);

private:
  std::filesystem::path dir_;
  Type type_;
  bool loaded_;
};

} // namespace appl
} // namespace lviz

#endif
