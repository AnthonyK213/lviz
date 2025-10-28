#include "bind.h"

#include "../gp/ax1.h"
#include "../gp/ax2.h"
#include "../gp/glm.h"

void lviz::bind::BindGP(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("gp")
      .beginClass<gp::Pnt>("Pnt")
      .addConstructor<void(), void(float, float, float)>()
      .endClass()
      .beginClass<gp::Vec>("Vec")
      .addConstructor<void(), void(float, float, float)>()
      .endClass()
      .beginClass<gp::Ax1>("Ax1")
      .addConstructor<void(), void(const gp::Pnt &, const gp::Vec &)>()
      .addFunction("Location", &gp::Ax1::Location)
      .addFunction("Direction", &gp::Ax1::Direction)
      .endClass()
      .beginClass<gp::Ax2>("Ax2")
      .addConstructor<void(), void(const gp::Pnt &, const gp::Vec &),
                      void(const gp::Pnt &, const gp::Vec &, const gp::Vec &)>()
      .addFunction("Axis", &gp::Ax2::Axis)
      .addFunction("Location", &gp::Ax2::Location)
      .addFunction("Direction", &gp::Ax2::Direction)
      .addFunction("XDirection", &gp::Ax2::XDirection)
      .addFunction("YDirection", &gp::Ax2::YDirection)
      .addFunction("Evaluate", &gp::Ax2::Evaluate)
      .endClass()
      .endNamespace()
      .endNamespace();
}
