#include "bind.h"

#include "../ui/view3d.h"

#include <LuaBridge/LuaBridge.h>

void lviz::bind::BindView3d(lua_State *L, ui::View3d *view3d) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("view3d")
      .addFunction("DrawPoint",
                   [view3d](const glm::vec3 &point) -> bool {
                     return view3d->DrawPoint(point);
                   })
      .addFunction(
          "DrawLine",
          [view3d](const glm::vec3 &point1, const glm::vec3 &point2) -> bool {
            return view3d->DrawLine(point1, point2);
          })
      .addFunction(
          "DrawTriangle",
          [view3d](const glm::vec3 &point1, const glm::vec3 &point2,
                   const glm::vec3 &point3) -> bool {
            return view3d->DrawTriangle(point1, point2, point3);
          },
          [view3d](const glm::vec3 &point1, const glm::vec3 &point2,
                   const glm::vec3 &point3, const glm::vec3 &normal1,
                   const glm::vec3 &normal2, const glm::vec3 &normal3) -> bool {
            return view3d->DrawTriangle(point1, point2, point3, normal1,
                                        normal2, normal3);
          })
      .addFunction("Purge", [view3d]() { view3d->Purge(); })
      .endNamespace()
      .endNamespace();
}
