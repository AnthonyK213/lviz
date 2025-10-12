#ifndef _LVIZ_UI_VIEWPORT_H
#define _LVIZ_UI_VIEWPORT_H

#include <glad/glad.h>

#include <wx/glcanvas.h>
#include <wx/wx.h>

namespace lviz::ui {

class Frame;

class Viewport : public wxGLCanvas {
public:
  Viewport(wxWindow *parent, const wxGLAttributes &attribs);

  ~Viewport();

  bool InitGLFuncs();
  bool InitGL();

  void OnPaint(wxPaintEvent &event);
  void OnSize(wxSizeEvent &event);
  
  void OnKeyDown(wxKeyEvent &event);

public:
  wxColour triangleColor{wxColour(255, 128, 51)};

private:
  wxGLContext *myGLCtxt;
  bool myGLIsInit;
  
  float anglex;
  float angley;

  unsigned int myVAO, myVBO, myEBO, myShader;
};

} // namespace lviz::ui

#endif
