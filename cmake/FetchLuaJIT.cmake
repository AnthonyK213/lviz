include(FetchContent)

FetchContent_Declare(
  LuaJIT_Source
  GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT
  GIT_TAG origin/v2.1
  GIT_SHALLOW 1
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  )

FetchContent_Declare(
  LuaJIT
  GIT_REPOSITORY https://github.com/zhaozg/luajit-cmake
  GIT_TAG 9ea79407064f67e2589deb0443a5305c53428159
  # GIT_TAG origin/master
  # GIT_SHALLOW 1
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/luajit-cmake
  )

FetchContent_GetProperties(LuaJIT_Source)
if(NOT luajit_source_POPULATED)
  FetchContent_Populate(LuaJIT_Source)
endif()

FetchContent_GetProperties(LuaJIT)
if(NOT luajit_POPULATED)
  FetchContent_Populate(LuaJIT)
  add_subdirectory(
    ${luajit_SOURCE_DIR}
    ${luajit_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )

  target_include_directories(
    buildvm
    PRIVATE
    ${luajit_BINARY_DIR}
    )

  if(WIN32)
    set_target_properties(libluajit PROPERTIES OUTPUT_NAME "lua51")
  endif()
endif()
