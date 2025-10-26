#include "bind.h"

#include "../appl/extension_manager.h"

void lviz::bind::BindAppl(lua_State *L, appl::ExtensionManager *manager) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("appl")
      .beginClass<appl::Extension>("Extension")
      .addFunction("IsValid", &appl::Extension::IsValid)
      .addFunction("IsLoaded", &appl::Extension::IsLoaded)
      .addFunction("GetPath", &appl::Extension::GetPath)
      .addFunction("GetName", &appl::Extension::GetName)
      .endClass()
      .addFunction(
          "GetExtension",
          [manager](const std::string &name) -> const appl::Extension * {
            for (const appl::Extension &ext : manager->GetExtensions()) {
              if (ext.GetName() == name) {
                return &ext;
              }
            }
            return nullptr;
          })
      .endNamespace()
      .endNamespace();
}
