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
                          void(const glm::vec3 &, const glm::vec3 &,
                               glm::f32)>()
      .endClass()
      .deriveClass<canvas::Line, canvas::Curve>("Line")
      .addConstructorFrom<canvas::handle<canvas::Line>,
                          void(const glm::vec3 &, const glm::vec3 &)>()
      .endClass()
      .deriveClass<canvas::Polyline, canvas::Curve>("Polyline")
      .addConstructorFrom<canvas::handle<canvas::Polyline>,
                          void(const std::vector<glm::vec3> &)>()
      .endClass()
      .deriveClass<canvas::Surface, canvas::Geometry>("Surface")
      .endClass()
      .deriveClass<canvas::Triangle, canvas::Surface>("Triangle")
      .addConstructorFrom<
          canvas::handle<canvas::Triangle>,
          void(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &),
          void(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
               const glm::vec3 &, const glm::vec3 &, const glm::vec3 &)>()
      .endClass()
      .endNamespace()
      .endNamespace();
}
