#ifndef _LVIZ_APP_APPLICATION_H
#define _LVIZ_APP_APPLICATION_H

#include <wx/wx.h>

namespace lviz::app {

class Application : public wxApp {
public:
  Application();

  bool OnInit() wxOVERRIDE;

private:
};

} // namespace lviz::app

#endif
