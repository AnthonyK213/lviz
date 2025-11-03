#include "bind.h"

#include "../window/gl_window.h"

void lviz::bind::BindUI(lua_State *L, window::GLWindow *gl_win) {
  ui::Log *log_buf = gl_win->GetLog();
  ui::View3d *view3d = gl_win->GetView3d();

  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("view3d")
      .addFunction(
          "Display",
          [view3d](const canvas::handle<canvas::Presentable> &obj) -> bool {
            return view3d->Display(obj);
          })
      .addFunction("Clear", [view3d]() { view3d->Clear(); })
      .endNamespace()
      .beginNamespace("log")
      .addFunction("Clear", [log_buf]() { log_buf->Clear(); })
      .endNamespace()
      .endNamespace();
}
