#include "bind.h"

#include <uv.h>

#include <lauxlib.h>

extern "C" {
int luaopen_luv(lua_State *L);
void luv_set_loop(lua_State *L, uv_loop_t *loop);
}

namespace lviz {
namespace bind {

void BindUV(lua_State *L) {
  uv_loop_t *default_loop = uv_default_loop();
  luv_set_loop(L, default_loop);

  luaopen_luv(L);
  luabridge::LuaRef luv_table = luabridge::LuaRef::fromStack(L, -1);
  lua_pop(L, 1);

  luabridge::LuaRef lviz_table = luabridge::getGlobal(L, "lviz");
  if (lviz_table.isNil()) {
    lviz_table = luabridge::newTable(L);
    luabridge::setGlobal(L, lviz_table, "lviz");
  }

  lviz_table["uv"] = std::move(luv_table);
}

} // namespace bind
} // namespace lviz
