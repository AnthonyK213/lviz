#ifndef _LVIZ_UI_LOG_H
#define _LVIZ_UI_LOG_H

#include <deque>
#include <string>

namespace lviz {
namespace window {

class Window;

}

namespace ui {

class Log {
public:
  Log(window::Window *parent);

  ~Log();

  void Render();

  void Print(const std::string &message);

  void Clear();

private:
  window::Window *parent_;
  std::deque<std::string> buffer_;
  int max_size_;
};

} // namespace ui
} // namespace lviz

#endif
