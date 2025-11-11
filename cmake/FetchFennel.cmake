include(FetchContent)

FetchContent_Declare(
  fennel
  URL https://fennel-lang.org/downloads/fennel-1.6.0.lua
  URL_HASH SHA256=e8cc76d1de750d7f9d2023c3f2ea4525ec13a19e8e806e96d5159bcd2d3c0520
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/deps/fennel
  DOWNLOAD_NO_EXTRACT TRUE
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  )

FetchContent_GetProperties(fennel)
if(NOT fennel_source_POPULATED)
  FetchContent_Populate(fennel)
endif()
