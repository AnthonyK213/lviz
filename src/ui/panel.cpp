#include "panel.h"

#include "../appl/application.h"
#include "../window/gl_window.h"

#include <imgui.h>

#include <iostream>

namespace lviz {
namespace ui {

static const char *PROJ_LIST[] = {"Orthographic", "Perspective"};

static canvas::Camera::ProjectionType idxToProjType(int idx) {
  return static_cast<canvas::Camera::ProjectionType>(idx);
}

static appl::Application *getApplication(window::Window *win) {
  window::GLWindow *gl_win = dynamic_cast<window::GLWindow *>(win);
  return gl_win ? gl_win->GetApp() : nullptr;
}

static ui::View3d *getView3d(window::Window *win) {
  window::GLWindow *gl_win = dynamic_cast<window::GLWindow *>(win);
  return gl_win ? gl_win->GetView3d() : nullptr;
}

Panel::Panel(window::Window *parent)
    : parent_(parent), file_dialog_(), current_file_(), current_proj_idx_(0),
      show_grid_(true) {
  file_dialog_.SetTitle("Open script");
#ifndef LVIZ_ENABLE_FENNEL_SUPPORT
  file_dialog_.SetTypeFilters({".lua"});
#else
  file_dialog_.SetTypeFilters({".lua", ".fnl"});
#endif
}

Panel::~Panel() {}

void Panel::Setup() {
  setupProjection();
  setupShowGrid();
}

void Panel::Render() {
  ImGui::Begin("Control panel");

  if (ImGui::CollapsingHeader("View3d")) {
    if (ImGui::Combo("Projection", &current_proj_idx_, PROJ_LIST,
                     IM_ARRAYSIZE(PROJ_LIST))) {
      setupProjection();
    }

    if (ImGui::Checkbox("Show grid", &show_grid_)) {
      setupShowGrid();
    }

    if (ImGui::Button("Zoom all")) {
      ui::View3d *view3d = getView3d(parent_);
      if (view3d)
        view3d->ZoomAll();
    }

    if (ImGui::Button("Clear scene")) {
      ui::View3d *view3d = getView3d(parent_);
      if (view3d)
        view3d->Clear();
    }
  }

  if (ImGui::CollapsingHeader("Script")) {
    if (ImGui::Button("Open script")) {
      file_dialog_.Open();
    }

    if (ImGui::Button("Run script")) {
      appl::Application *app = getApplication(parent_);
      if (app) {
        appl::State *state = app->GetState();
        if (state) {
          std::string error{};
          if (!state->DoFile(current_file_, error))
            std::cout << error << std::endl;
        }
      }
    }
  }

  ImGui::End();

  file_dialog_.Display();
  if (file_dialog_.HasSelected()) {
    current_file_ = file_dialog_.GetSelected().string();
    file_dialog_.ClearSelected();
  }
}

void Panel::setupProjection() {
  ui::View3d *view3d = getView3d(parent_);
  if (view3d) {
    canvas::Camera *camera = view3d->GetCamera();
    if (camera)
      camera->SetProjType(idxToProjType(current_proj_idx_));
  }
}

void Panel::setupShowGrid() {
  ui::View3d *view3d = getView3d(parent_);
  if (view3d)
    view3d->SetShowGrid(show_grid_);
}

} // namespace ui
} // namespace lviz
