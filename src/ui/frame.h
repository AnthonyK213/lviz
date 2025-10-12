#ifndef _LVIZ_UI_FRAME_H
#define _LVIZ_UI_FRAME_H

#include <wx/wx.h>

namespace lviz::ui {

class Viewport;

class Frame : public wxFrame {
public:
  Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

  void SetupMainMenu();

private:
  Viewport *myViewport;
};

} // namespace lviz::ui

#endif
