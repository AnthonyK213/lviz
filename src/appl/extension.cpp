#include "extension.h"
#include "application.h"
#include "extension_manager.h"

namespace lviz {
namespace appl {

Extension::Extension(const std::filesystem::path &dir)
    : dir_(dir), type_(Type::None), loaded_(false) {
  if (!std::filesystem::is_directory(dir_))
    return;

  std::filesystem::path dir_lua = dir_ / "lua";
  if (!std::filesystem::is_directory(dir_lua))
    return;

  std::filesystem::path dir_lua_main = dir_lua / "main.lua";
  if (std::filesystem::is_regular_file(dir_lua_main))
    type_ = Type::Executable;
  else
    type_ = Type::Library;
}

void Extension::Load(ExtensionManager *manager) {
  if (IsLoaded() || !IsValid())
    return;

  State *state = manager->GetApp()->GetState();
  std::string dir_lua = (dir_ / "lua").string();
  state->PathAppend(dir_lua + "/?.lua");
#if defined(_WIN32)
  state->CPathAppend(dir_lua + "/?.dll");
#elif defined(__linux__)
  state->CPathAppend(dir_lua + "/?.so");
#elif defined(__APPLE__)
  state->CPathAppend(dir_lua + "/?.dylib");
#endif

  /* TODO: Load executable. */

  loaded_ = true;
}

} // namespace appl
} // namespace lviz
