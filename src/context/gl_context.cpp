#include "gl_context.h"

#include "../window/window.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace lviz {
namespace context {

static void onKeyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods) {
  auto p_win = static_cast<window::Window *>(glfwGetWindowUserPointer(window));
  p_win->OnKey(key, scancode, action, mods);
}

static void onScrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset) {
  auto p_win = static_cast<window::Window *>(glfwGetWindowUserPointer(window));
  p_win->OnScroll(yoffset);
}

static void onWindowSizeCallback(GLFWwindow *window, int width, int height) {
  auto p_win = static_cast<window::Window *>(glfwGetWindowUserPointer(window));
  p_win->OnResize(width, height);
}

static void onWindowCloseCallback(GLFWwindow *window) {
  auto p_win = static_cast<window::Window *>(glfwGetWindowUserPointer(window));
  p_win->OnClose();
}

GLContext::GLContext() : Context() {}

bool GLContext::Init(window::Window *win) {
  Context::Init(win);

  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window with graphics context
  GLFWwindow *gl_win =
      glfwCreateWindow(win->GetWidth(), win->GetHeight(),
                       win->GetTitle().c_str(), nullptr, nullptr);
  win->SetNativeWindow(gl_win);

  if (!gl_win)
    return false;

  glfwSetWindowUserPointer(gl_win, win);
  glfwSetKeyCallback(gl_win, onKeyCallback);
  glfwSetScrollCallback(gl_win, onScrollCallback);
  glfwSetWindowSizeCallback(gl_win, onWindowSizeCallback);
  glfwSetWindowCloseCallback(gl_win, onWindowCloseCallback);
  glfwMakeContextCurrent(gl_win);
  glfwSwapInterval(1); // Enable vsync

  // Load GL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    return false;

  glEnable(GL_DEPTH_TEST);

  return true;
}

void GLContext::PreRender() {
  // Idle...
  glfwWaitEvents();

  glViewport(0, 0, window_->GetWidth(), window_->GetHeight());
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::PostRender() {
  glfwPollEvents();
  glfwSwapBuffers((GLFWwindow *)window_->GetNativeWindow());
}

void GLContext::Close() {
  glfwDestroyWindow((GLFWwindow *)window_->GetNativeWindow());
  glfwTerminate();
}

} // namespace context
} // namespace lviz
