include(FetchContent)

FetchContent_Declare(
  luv
  URL https://github.com/luvit/luv/releases/download/1.53.0-1/luv-1.53.0-1.tar.gz
  URL_HASH SHA256=569b488d5d31609ea466a6c70e008a42661ec773ea1584d3d766d46280ab7cf4
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/luv
  )

set(BUILD_MODULE OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)

set(WITH_SHARED_LIBUV ON CACHE BOOL "" FORCE)

set(LIBUV_INCLUDE_DIR "${libuv_SOURCE_DIR}/src" CACHE PATH "" FORCE)
set(LIBUV_LIBRARIES uv_a CACHE STRING "" FORCE)

set(WITH_LUA_ENGINE "LuaJIT" CACHE STRING "" FORCE)
set(LUA_BUILD_TYPE "System" CACHE STRING "" FORCE)

set(LuaJIT_FOUND TRUE CACHE BOOL "" FORCE)
set(LUAJIT_FOUND TRUE CACHE BOOL "" FORCE)
set(LuaJIT_INCLUDE_DIRS "${LUAJIT_DIR}/src" CACHE PATH "" FORCE)
set(LUAJIT_INCLUDE_DIR "${LUAJIT_DIR}/src" CACHE PATH "" FORCE)
set(LuaJIT_LIBRARIES luajit::lib luajit::header CACHE STRING "" FORCE)
set(LUAJIT_LIBRARIES luajit::lib luajit::header CACHE STRING "" FORCE)

set(LUA_INCLUDE_DIR "${LUAJIT_DIR}/src" CACHE PATH "" FORCE)
set(LUA_LIBRARIES luajit::lib luajit::header CACHE STRING "" FORCE)

FetchContent_GetProperties(luv)
if(NOT luv_POPULATED)
  FetchContent_Populate(luv)
  add_subdirectory(
    ${luv_SOURCE_DIR}
    ${luv_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
