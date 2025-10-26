#include "bind.h"

#include <glm/glm.hpp>

void lviz::bind::BindGLM(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("glm")
      .beginClass<glm::vec3>("vec3")
      .addConstructor<void(), void(float, float, float)>()
      .endClass()
      .endNamespace()
      .endNamespace();
}
