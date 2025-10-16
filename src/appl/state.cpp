#include "state.h"

namespace lviz {
namespace appl {

State::State() : lua_(nullptr) {}

State::~State() {
  lua_close(lua_);
}

bool State::Init() {
  if (lua_)
    return false;

  lua_ = luaL_newstate();

  if (!lua_)
    return false;

  lua_gc(lua_, LUA_GCSTOP, 0);
  luaL_openlibs(lua_);
  lua_gc(lua_, LUA_GCRESTART, -1);

  return true;
}

bool State::DoFile(const std::string &file_path, std::string &error) {
  if (luaL_dofile(lua_, file_path.c_str()) != 0) {
    error = lua_tostring(lua_, -1);
    lua_pop(lua_, -1);
    return false;
  }
  return true;
}

bool State::PathAppend(const std::string &path) {
  lua_getglobal(lua_, "package");
  lua_getfield(lua_, -1, "path");

  std::string lua_path = lua_tostring(lua_, -1);
  if (!lua_path.empty())
    lua_path.push_back(';');
  lua_path.append(path);

  lua_pop(lua_, 1);
  lua_pushstring(lua_, lua_path.c_str());
  lua_setfield(lua_, -2, "path");
  lua_pop(lua_, 1);

  return true;
}

bool State::CPathAppend(const std::string &path) {
  lua_getglobal(lua_, "package");
  lua_getfield(lua_, -1, "cpath");

  std::string lua_cpath = lua_tostring(lua_, -1);
  if (!lua_cpath.empty())
    lua_cpath.push_back(';');
  lua_cpath.append(path);

  lua_pop(lua_, 1);
  lua_pushstring(lua_, lua_cpath.c_str());
  lua_setfield(lua_, -2, "cpath");
  lua_pop(lua_, 1);

  return true;
}

} // namespace appl
} // namespace lviz
