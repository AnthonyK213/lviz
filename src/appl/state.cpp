#include "state.h"

namespace lviz {
namespace appl {

State::State() : lua_(nullptr) {
  lua_ = luaL_newstate();

  lua_gc(lua_, LUA_GCSTOP, 0);
  luaL_openlibs(lua_);
  lua_gc(lua_, LUA_GCRESTART, -1);
}

State::~State() {
  lua_close(lua_);
}

} // namespace appl
} // namespace lviz
