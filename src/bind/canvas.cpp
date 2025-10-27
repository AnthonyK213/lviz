#include "bind.h"

#include "../canvas/circle.h"
#include "../canvas/line.h"
#include "../canvas/polyline.h"
#include "../canvas/triangle.h"

void lviz::bind::BindCanvas(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("canvas")
      .beginClass<canvas::Object>("Object")
      .addFunction("GetRefCount", &canvas::Object::GetRefCount)
      .endClass()
      .deriveClass<canvas::Geometry, canvas::Object>("Geometry")
      .endClass()
      .deriveClass<canvas::Curve, canvas::Geometry>("Curve")
      .endClass()
      .deriveClass<canvas::Circle, canvas::Curve>("Circle")
      .addConstructorFrom<canvas::handle<canvas::Circle>,
                          void(const gp::Ax2 &position, glm::f32 radius)>()
      .endClass()
      .deriveClass<canvas::Line, canvas::Curve>("Line")
      .addConstructorFrom<canvas::handle<canvas::Line>,
                          void(const gp::Pnt &, const gp::Pnt &)>()
      .endClass()
      .deriveClass<canvas::Polyline, canvas::Curve>("Polyline")
      .addConstructorFrom<canvas::handle<canvas::Polyline>,
                          void(const std::vector<gp::Pnt> &)>()
      .endClass()
      .deriveClass<canvas::Surface, canvas::Geometry>("Surface")
      .endClass()
      .deriveClass<canvas::Triangle, canvas::Surface>("Triangle")
      .addConstructorFrom<
          canvas::handle<canvas::Triangle>,
          void(const gp::Pnt &, const gp::Pnt &, const gp::Pnt &),
          void(const gp::Pnt &, const gp::Pnt &, const gp::Pnt &,
               const gp::Vec &, const gp::Vec &, const gp::Vec &)>()
      .endClass()
      .endNamespace()
      .endNamespace();
}
