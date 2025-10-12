aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/app LVIZ_SRC_APP)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ui LVIZ_SRC_UI)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/view LVIZ_SRC_VIEW)

set(
  LVIZ_SRC
  ${GLAD_DIR}/src/glad.c
  ${LVIZ_SRC_APP}
  ${LVIZ_SRC_UI}
  ${LVIZ_SRC_VIEW}
  main.cpp
  )

if (APPLE)
  add_executable(
    ${PROJECT_NAME}
    MACOSX_BUNDLE
    ${LVIZ_SRC}
    )

  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
else()
  add_executable(
    ${PROJECT_NAME}
    WIN32
    ${LVIZ_SRC}
    lviz.exe.manifest
    )
endif()

include(${wxWidgets_USE_FILE})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${GLAD_DIR}/include/
  ${glm_SOURCE_DIR}
  ${luajit_BINARY_DIR}
  )

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  OpenGL::GL
  ${wxWidgets_LIBRARIES}
  )

if(APPLE)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    -Wl,-export_dynamic
    luajit::lib
    luajit::header
    )
elseif(UNIX)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    -Wl,-E
    luajit::lib
    luajit::header
    )
else()
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    luajit::lib
    luajit::header
    )
endif()

if(MSVC)
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:libluajit,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
    )
endif(MSVC)
