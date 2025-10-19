#include "bind.h"

#include "../appl/extension.h"

#include <LuaBridge/LuaBridge.h>

void lviz::bind::BindExtension(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("appl")
      .beginClass<appl::Extension>("Extension")
      .addFunction("IsValid", &appl::Extension::IsValid)
      .addFunction("IsLoaded", &appl::Extension::IsLoaded)
      .addFunction("GetPath", &appl::Extension::GetPath)
      .addFunction("GetName", &appl::Extension::GetName)
      .endClass()
      .endNamespace()
      .endNamespace();
}
