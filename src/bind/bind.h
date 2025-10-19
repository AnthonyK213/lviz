#ifndef _LVIZ_BIND_BIND_H
#define _LVIZ_BIND_BIND_H

#include <lua.hpp>

namespace lviz {
namespace appl {

class ExtensionManager;

} // namespace appl

namespace ui {

class View3d;

} // namespace ui

namespace bind {

void BindGLM(lua_State *L);

void BindView3d(lua_State *L, ui::View3d *view3d);

void BindExtension(lua_State *L);

void BindExtensionManager(lua_State *L, appl::ExtensionManager *manager);

} // namespace bind
} // namespace lviz

#endif
