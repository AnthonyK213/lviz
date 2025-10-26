#ifndef _LVIZ_BIND_BIND_H
#define _LVIZ_BIND_BIND_H

#include <lua.hpp>

#include <LuaBridge/LuaBridge.h>

#include <LuaBridge/Array.h>
#include <LuaBridge/Vector.h>

#include "../canvas/handle.h"

namespace luabridge {

template <class T> struct ContainerTraits<lviz::canvas::handle<T>> {
  using Type = T;

  static lviz::canvas::handle<T> construct(T *c) {
    return c;
  }

  static T *get(const lviz::canvas::handle<T> &c) {
    return c.get();
  }
};

} // namespace luabridge

namespace lviz {
namespace appl {

class ExtensionManager;

} // namespace appl

namespace ui {

class View3d;

} // namespace ui

namespace bind {

void BindGLM(lua_State *L);

void BindCanvas(lua_State *L);

void BindAppl(lua_State *L, appl::ExtensionManager *manager);

void BindUI(lua_State *L, ui::View3d *view3d);

} // namespace bind
} // namespace lviz

#endif
