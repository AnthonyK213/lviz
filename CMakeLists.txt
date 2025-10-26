cmake_minimum_required(VERSION 3.20)

project(
  lviz
  VERSION 0.0.1
  LANGUAGES C CXX
  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION})

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory 
  (or any directory with a CMakeLists.txt file). Please make a 
  build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

if(MSVC)
  option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
else(MSVC)
  option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
endif(MSVC)

set(OpenGL_GL_PREFERENCE "GLVND")

# find_package(OpenGL REQUIRED)
# message("OpenGL: ${OPENGL_gl_LIBRARY}")

set(LUAJIT_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source CACHE STRING "Path of LuaJIT 2.1 source dir")

include(cmake/FetchGLFW.cmake)
include(cmake/FetchGLM.cmake)
include(cmake/FetchImGui.cmake)
include(cmake/FetchLuaJIT.cmake)
include(cmake/FetchLuaBridge3.cmake)

# GLAD
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/deps/glad)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include/)

# ImGui
set(IMGUI_DIR ${CMAKE_BINARY_DIR}/deps/imgui)
add_library(
  imgui
  STATIC
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  )
target_include_directories(
  imgui
  PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends/
  ${glfw_SOURCE_DIR}/include/
  )

# lviz
add_subdirectory(src)
