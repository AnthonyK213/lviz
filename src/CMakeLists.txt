set(
  IMGUI_SRC
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/appl LVIZ_APPL_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/canvas LVIZ_CANVAS_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/render LVIZ_RENDER_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ui LVIZ_UI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/window LVIZ_WINDOW_SRC)

set(
  LVIZ_SRC
  ${GLAD_DIR}/src/glad.c
  ${IMGUI_SRC}
  ${LVIZ_APPL_SRC}
  ${LVIZ_CANVAS_SRC}
  ${LVIZ_RENDER_SRC}
  ${LVIZ_UI_SRC}
  ${LVIZ_WINDOW_SRC}
  main.cpp
  )

if (APPLE)
  add_executable(
    lviz
    MACOSX_BUNDLE
    ${LVIZ_SRC}
    )

  set_target_properties(
    lviz
    PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/rc/Info.plist
    )
elseif(WIN32)
  add_executable(
    lviz
    WIN32
    ${LVIZ_SRC}
    rc/lviz.rc
    )
else()
  add_executable(
    lviz
    ${LVIZ_SRC}
    )
endif()

target_include_directories(
  lviz
  PRIVATE
  ${GLAD_DIR}/include/
  ${PLUGINS_DIR}/imgui/
  ${glfw_SOURCE_DIR}/include/
  ${glm_SOURCE_DIR}
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends/
  ${luajit_BINARY_DIR}
  )

target_link_libraries(
  lviz
  PRIVATE
  OpenGL::GL
  glfw
  )

if(APPLE)
  target_link_libraries(
    lviz
    PRIVATE
    -Wl,-export_dynamic
    luajit::lib
    luajit::header
    )
elseif(UNIX)
  target_link_libraries(
    lviz
    PRIVATE
    -Wl,-E
    luajit::lib
    luajit::header
    )
else()
  target_link_libraries(
    lviz
    PRIVATE
    luajit::lib
    luajit::header
    )
endif()

if(MSVC)
  add_custom_command(
    TARGET lviz POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:glfw,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
        "$<TARGET_PROPERTY:lviz,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:libluajit,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
        "$<TARGET_PROPERTY:lviz,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>"
    )
endif(MSVC)
