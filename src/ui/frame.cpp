#include "frame.h"
#include "viewport.h"

#include <wx/gbsizer.h>
#include <wx/splitter.h>

namespace lviz::ui {

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), myViewport(nullptr) {
  SetupMainMenu();

  wxGLAttributes vAttrs;
  vAttrs.PlatformDefaults().Defaults().EndList();
  if (!wxGLCanvas::IsDisplaySupported(vAttrs)) {
    wxMessageBox("OpenGl display is unsupported.", "OpenGL unsupported.",
                 wxOK | wxICON_INFORMATION, this);
  }

  wxGridBagSizer *sizer = new wxGridBagSizer(FromDIP(5), FromDIP(5));

  wxPanel *controlPanel = new wxPanel(this, wxID_ANY);

  controlPanel->SetBackgroundColour(wxColor(200, 100, 100));
  controlPanel->SetMinSize(FromDIP(wxSize{200, 300}));

  wxSplitterWindow *splitter =
      new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxSP_BORDER | wxSP_LIVE_UPDATE);

  myViewport = new Viewport(splitter, vAttrs);
  wxPanel *replPanel = new wxPanel(splitter);

  replPanel->SetBackgroundColour(wxColor(200, 200, 100));
  replPanel->SetMinSize(FromDIP(wxSize{400, 100}));

  myViewport->SetMinSize(FromDIP(wxSize{640, 480}));
  myViewport->SetFocus();

  splitter->SetMinimumPaneSize(100);
  splitter->SplitHorizontally(myViewport, replPanel);

  sizer->Add(controlPanel, {0, 0}, {1, 1}, wxEXPAND);
  sizer->Add(splitter, {0, 1}, {1, 1}, wxEXPAND);

  sizer->AddGrowableRow(0);
  sizer->AddGrowableCol(1);

  SetSizerAndFit(sizer);

  myViewport->Bind(wxEVT_ENTER_WINDOW,
                   [this](wxMouseEvent &event) { myViewport->SetFocus(); });
}

void Frame::SetupMainMenu() {
  wxMenuBar *menuBar = new wxMenuBar();

  wxMenu *fileMenu = new wxMenu();
  fileMenu->Append(wxID_NEW);
  fileMenu->Append(wxID_OPEN);
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_SAVE);
  fileMenu->Append(wxID_SAVEAS);

  wxMenu *editMenu = new wxMenu();
  editMenu->Append(wxID_UNDO);
  editMenu->Append(wxID_REDO);
  editMenu->AppendSeparator();
  editMenu->Append(wxID_CUT);
  editMenu->Append(wxID_COPY);
  editMenu->Append(wxID_PASTE);

  menuBar->Append(fileMenu, "&File");
  menuBar->Append(editMenu, "&Edit");

  SetMenuBar(menuBar);
}

} // namespace lviz::ui
