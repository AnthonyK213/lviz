#ifndef _LVIZ_APPL_STATE_H
#define _LVIZ_APPL_STATE_H

#include <lua.hpp>

namespace lviz {
namespace appl {

class State {
public:
  State();

  ~State();

private:
  lua_State *lua_;
};

} // namespace appl
} // namespace lviz

#endif
