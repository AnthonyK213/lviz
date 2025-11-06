include(FetchContent)

FetchContent_Declare(
  latin-modern
  URL https://www.gust.org.pl/projects/e-foundry/latin-modern/download/lm2.006otf.zip
  URL_HASH SHA256=608a6f3de9fbafd70f977fbf21ca32850178dd19b11530385358840c8f291f06
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/latin-modern
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  )

FetchContent_GetProperties(latin-modern)
if(NOT latin-modern_source_POPULATED)
  FetchContent_Populate(latin-modern)
endif()
