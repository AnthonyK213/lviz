#ifndef _LVIZ_BIND_VIEW3D_H
#define _LVIZ_BIND_VIEW3D_H

#include <lua.hpp>

namespace lviz {
namespace ui {

class View3d;

} // namespace ui

namespace bind {

void BindView3d(lua_State *L, ui::View3d *view3d);

} // namespace bind
} // namespace lviz

#endif
