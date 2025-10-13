#ifndef _LVIZ_APPL_STATE_H
#define _LVIZ_APPL_STATE_H

#include <lua.hpp>

#include <string>

namespace lviz {
namespace appl {

class State {
public:
  State();

  ~State();

  bool Init();

  lua_State *GetLuaState() const {
    return lua_;
  }

  bool DoFile(const std::string &file_path, std::string &error);

  bool PathAppend(const std::string &path);

  bool CPathAppend(const std::string &path);

private:
  lua_State *lua_;
};

} // namespace appl
} // namespace lviz

#endif
