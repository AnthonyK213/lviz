include(FetchContent)

FetchContent_Declare(
  freetype
  URL https://download.savannah.gnu.org/releases/freetype/freetype-2.14.1.tar.gz
  URL_HASH SHA256=174d9e53402e1bf9ec7277e22ec199ba3e55a6be2c0740cb18c0ee9850fc8c34
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/freetype
  )

FetchContent_GetProperties(freetype)
if(NOT freetype_source_POPULATED)
  FetchContent_Populate(freetype)
  add_subdirectory(
    ${freetype_SOURCE_DIR}
    ${freetype_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
