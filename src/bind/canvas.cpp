#include "bind.h"

#include "../canvas/circle.h"
#include "../canvas/ellipse.h"
#include "../canvas/line.h"
#include "../canvas/point.h"
#include "../canvas/polyline.h"
#include "../canvas/triangle.h"
#include "../canvas/trimmed_curve.h"

void lviz::bind::BindCanvas(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("canvas")
      .beginClass<canvas::Object>("Object")
      .addFunction("GetRefCount", &canvas::Object::GetRefCount)
      .endClass()
      .deriveClass<canvas::Presentable, canvas::Object>("Presentable")
      .endClass()
      .deriveClass<canvas::Geometry, canvas::Presentable>("Geometry")
      .endClass()
      .deriveClass<canvas::Point, canvas::Geometry>("Point")
      .addConstructorFrom<canvas::handle<canvas::Point>, void(const gp::Pnt &),
                          void(glm::f32, glm::f32, glm::f32)>()
      .endClass()
      .deriveClass<canvas::Curve, canvas::Geometry>("Curve")
      .endClass()
      .deriveClass<canvas::Circle, canvas::Curve>("Circle")
      .addConstructorFrom<canvas::handle<canvas::Circle>,
                          void(const gp::Ax2 &, glm::f32)>()
      .endClass()
      .deriveClass<canvas::Ellipse, canvas::Curve>("Ellipse")
      .addConstructorFrom<canvas::handle<canvas::Ellipse>,
                          void(const gp::Ax2 &, glm::f32, glm::f32)>()
      .endClass()
      .deriveClass<canvas::Line, canvas::Curve>("Line")
      .addConstructorFrom<canvas::handle<canvas::Line>,
                          void(const gp::Pnt &, const gp::Pnt &)>()
      .endClass()
      .deriveClass<canvas::Polyline, canvas::Curve>("Polyline")
      .addConstructorFrom<canvas::handle<canvas::Polyline>,
                          void(const std::vector<gp::Pnt> &)>()
      .endClass()
      .deriveClass<canvas::TrimmedCurve, canvas::Curve>("TrimmedCurve")
      .addConstructorFrom<canvas::handle<canvas::TrimmedCurve>,
                          void(const canvas::handle<canvas::Curve> &, glm::f32,
                               glm::f32)>()
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
