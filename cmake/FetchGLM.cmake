include(FetchContent)

FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz
  URL_HASH SHA256=9f3174561fd26904b23f0db5e560971cbf9b3cbda0b280f04d5c379d03bf234c
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/glm
  )

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(
    ${glm_SOURCE_DIR}
    ${glm_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
