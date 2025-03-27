cmake_minimum_required(VERSION 3.20)

project(
  lviz
  VERSION 0.0.1
  LANGUAGES CXX
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

set(LUAJIT_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source CACHE STRING "Path of LuaJIT 2.1 source dir")
set(IMGUI_DIR ${CMAKE_BINARY_DIR}/deps/imgui CACHE STRING "Path of ImGui source dir")

find_package(OpenGL)

include(cmake/FetchGLFW.cmake)
include(cmake/FetchImGui.cmake)
include(cmake/FetchLuaJIT.cmake)

add_subdirectory(src)
