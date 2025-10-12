cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

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

find_package(OpenGL)
message("OpenGL: ${OPENGL_gl_LIBRARY}")

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/deps/glad CACHE STRING "Path of GLAD source dir")
set(LUAJIT_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source CACHE STRING "Path of LuaJIT 2.1 source dir")

include(cmake/FetchGLM.cmake)
include(cmake/FetchLuaJIT.cmake)

set(ENV{WX_CONFIG} ${WX_DIR}/bin/wx-config)
find_package(wxWidgets COMPONENTS core base gl REQUIRED)
message("wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")

add_subdirectory(src)
