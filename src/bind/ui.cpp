#include "bind.h"

#include "../ui/view3d.h"

void lviz::bind::BindUI(lua_State *L, ui::View3d *view3d) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("view3d")
      .addFunction(
          "AddGeometry",
          [view3d](const canvas::handle<canvas::Geometry> &geom) -> bool {
            return view3d->AddGeometry(geom);
          })
      .addFunction("Purge", [view3d]() { view3d->Purge(); })
      .endNamespace()
      .endNamespace();
}
