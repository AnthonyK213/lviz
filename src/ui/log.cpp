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

  for (const std::string &line : buffer_) {
    ImGui::Text(line.c_str());
  }

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
