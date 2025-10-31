#include "log.h"

#include "../window/gl_window.h"

#include <imgui.h>

#include <iostream>

namespace lviz {
namespace ui {

Log::Log(window::Window *parent)
    : parent_(parent), buffer_(), max_size_(9001) {}

Log::~Log() {}

void Log::Render() {
  ImGui::Begin("Log");

  if (ImGui::Button("Clear")) {
    Clear();
  }

  ImGui::BeginChild("Log buffer", ImVec2(0, 0), ImGuiChildFlags_Borders);
  for (const std::string &line : buffer_) {
    ImGui::TextWrapped("%s", line.c_str());
  }
  ImGui::EndChild();

  ImGui::End();
}

void Log::Print(const std::string &message) {
  if (buffer_.size() >= max_size_)
    buffer_.pop_front();
  buffer_.push_back(message);
}

void Log::Clear() {
  buffer_.clear();
}

} // namespace ui
} // namespace lviz
