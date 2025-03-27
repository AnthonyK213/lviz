include(FetchContent)

FetchContent_Declare(
  imgui
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.tar.gz
  URL_HASH SHA256=8e1bbc76c71d74fef2fb85db7e7ca8eba13d6a86623c54992b60162db554ffdb
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/imgui
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  )

FetchContent_GetProperties(imgui)
if(NOT imgui_source_POPULATED)
  FetchContent_Populate(imgui)
endif()
