#include "bind.h"

#include "../appl/extension_manager.h"

#include <LuaBridge/LuaBridge.h>

void lviz::bind::BindExtensionManager(lua_State *L,
                                      appl::ExtensionManager *manager) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("lviz")
      .beginNamespace("appl")
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
