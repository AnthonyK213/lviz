include(FetchContent)

FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
  URL_HASH SHA256=c038d34200234d071fae9345bc455e4a8f2f544ab60150765d7704e08f3dac01
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/glfw
  )

FetchContent_GetProperties(glfw)
if(NOT glfw_source_POPULATED)
  FetchContent_Populate(glfw)
  add_subdirectory(
    ${glfw_SOURCE_DIR}
    ${glfw_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
