#include "bind.h"

#include "../gp/ax1.h"
#include "../gp/ax2.h"
#include "../gp/glm.h"

static glm::vec3 xyzAdded(const glm::vec3 &xyz1, const glm::vec3 &xyz2) {
  return xyz1 + xyz2;
}

static glm::vec3 xyzSubtracted(const glm::vec3 &xyz1, const glm::vec3 &xyz2) {
  return xyz1 - xyz2;
}

static glm::vec3 xyzMultiplied(const glm::vec3 &xyz, glm::f32 scale) {
  return xyz * scale;
}

static glm::vec3 xyzDivided(const glm::vec3 &xyz, glm::f32 scale) {
  return xyz / scale;
}

static glm::vec3 xyzNegated(const glm::vec3 &xyz) {
  return -xyz;
}

void lviz::bind::BindGP(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("gp")
      .beginClass<gp::Pnt>("Pnt")
      .addConstructor<void(), void(const glm::vec3 &),
                      void(float, float, float)>()
      .addProperty("x", &gp::Pnt::x)
      .addProperty("y", &gp::Pnt::y)
      .addProperty("z", &gp::Pnt::z)
      .addFunction("IsUnset", &gp::IsUnsetXYZ)
      .addFunction("Distance", &gp::PntDistance)
      .addFunction("Distance2", &gp::PntDistance2)
      .addFunction("Added", &xyzAdded)
      .addFunction("Subtracted", &xyzSubtracted)
      .addFunction("Multiplied", &xyzMultiplied)
      .addFunction("Divided", &xyzDivided)
      .addFunction("Negated", &xyzNegated)
      .endClass()
      .beginClass<gp::Vec>("Vec")
      .addConstructor<void(), void(const glm::vec3 &),
                      void(float, float, float)>()
      .addProperty("x", &gp::Vec::x)
      .addProperty("y", &gp::Vec::y)
      .addProperty("z", &gp::Vec::z)
      .addFunction("IsUnset", &gp::IsUnsetXYZ)
      .addFunction("Magnitude", &gp::VecMagnitude)
      .addFunction("Added", &xyzAdded)
      .addFunction("Subtracted", &xyzSubtracted)
      .addFunction("Multiplied", &xyzMultiplied)
      .addFunction("Divided", &xyzDivided)
      .addFunction("Negated", &xyzNegated)
      .addFunction("Dot", &gp::VecDot)
      .addFunction("Crossed", &gp::VecCrossed)
      .addFunction("Angle", &gp::VecAngle)
      .addFunction("AngleWithRef", &gp::VecAngleWithRef)
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
      .addFunction("ToWorld", &gp::Ax2::ToWorld)
      .addFunction("ToLocal", &gp::Ax2::ToLocal)
      .endClass()
      .endNamespace()
      .endNamespace();
}
