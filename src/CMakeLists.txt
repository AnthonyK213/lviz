# Macro definitions.
if (${LVIZ_ENABLE_IMGUI_MULTI_VIEWPORT})
  add_definitions(-DLVIZ_ENABLE_IMGUI_MULTI_VIEWPORT)
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/appl LVIZ_APPL_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/bind LVIZ_BIND_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/canvas LVIZ_CANVAS_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/gp LVIZ_GP_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/render LVIZ_RENDER_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ui LVIZ_UI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/window LVIZ_WINDOW_SRC)

set(
  LVIZ_SRC
  ${LVIZ_APPL_SRC}
  ${LVIZ_BIND_SRC}
  ${LVIZ_CANVAS_SRC}
  ${LVIZ_GP_SRC}
  ${LVIZ_RENDER_SRC}
  ${LVIZ_UI_SRC}
  ${LVIZ_WINDOW_SRC}
  main.cpp
  )

if (APPLE)
  add_executable(lviz MACOSX_BUNDLE ${LVIZ_SRC})
  set_target_properties(
    lviz
    PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/rc/Info.plist
    )
elseif(WIN32)
  add_executable(lviz WIN32 ${LVIZ_SRC} rc/lviz.rc)
else()
  add_executable(lviz ${LVIZ_SRC})
endif()

target_include_directories(
  lviz
  PRIVATE
  ${CMAKE_BINARY_DIR}/deps/imgui-filebrowser/
  ${glm_SOURCE_DIR}
  ${luajit_BINARY_DIR}
  ${luabridge3_SOURCE_DIR}/Source
  )

target_link_libraries(lviz PRIVATE glad glfw imgui)

# Link X11 on Linux.
if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  message("X11: ${X11_LIBRARIES}")
  target_link_libraries(lviz PRIVATE ${X11_LIBRARIES})
endif()

# Link LuaJIT, should export dynamic symbols on unix-like platform.
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

add_custom_command(
  TARGET lviz POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
      "$<TARGET_PROPERTY:lviz,SOURCE_DIR>/../runtime"
      "$<TARGET_PROPERTY:lviz,BINARY_DIR>/$<$<BOOL:${CMAKE_CONFIGURATION_TYPES}>:$<CONFIG>>/runtime"
  )

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
