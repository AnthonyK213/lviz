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

add_executable(
  ${PROJECT_NAME}
  ${GLAD_DIR}/src/glad.c
  ${IMGUI_SRC}
  main.cpp
  )

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${GLAD_DIR}/include/
  ${glfw_SOURCE_DIR}/include/
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends/
  ${luajit_BINARY_DIR}
  )

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  OpenGL::GL
  glfw
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
        "$<TARGET_PROPERTY:glfw,BINARY_DIR>/$<CONFIG>"
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/$<CONFIG>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:libluajit,BINARY_DIR>/$<CONFIG>"
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/$<CONFIG>"
    )
endif(MSVC)
