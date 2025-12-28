cmake_minimum_required(VERSION 3.16)
project(windowing_gtk4 CXX)


message(STATUS "Project : ${PROJECT_NAME}")


#if(${HAS_WAYLAND})
#
#    set(XDG_SHELL_CLIENT_PROTOCOL_XML "/usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml")
#
#    set(XDG_SHELL_CLIENT_PROTOCOL_H "${CMAKE_CURRENT_SOURCE_DIR}/_operating_system/${SLASHED_OPERATING_SYSTEM}/include/xdg-shell-client-protocol.h")
#
#    add_custom_command(
#       OUTPUT ${XDG_SHELL_CLIENT_PROTOCOL_H}
#       COMMAND mkdir -p "${CMAKE_CURRENT_SOURCE_DIR}/${SLASHED_OPERATING_SYSTEM}/include"
#       COMMAND wayland-scanner client-header ${XDG_SHELL_CLIENT_PROTOCOL_XML} ${XDG_SHELL_CLIENT_PROTOCOL_H}
#       MAIN_DEPENDENCY ${XDG_SHELL_CLIENT_PROTOCOL_XML}
#    )
#
#    set(XDG_SHELL_CLIENT_PROTOCOL_C "${CMAKE_CURRENT_SOURCE_DIR}/_operating_system/${SLASHED_OPERATING_SYSTEM}/include/xdg-shell-client-protocol.c")
#
#    add_custom_command(
#       OUTPUT ${XDG_SHELL_CLIENT_PROTOCOL_C}
#       COMMAND mkdir -p "${CMAKE_CURRENT_SOURCE_DIR}/${SLASHED_OPERATING_SYSTEM}/include"
#       COMMAND wayland-scanner private-code ${XDG_SHELL_CLIENT_PROTOCOL_XML} ${XDG_SHELL_CLIENT_PROTOCOL_C}
#       MAIN_DEPENDENCY ${XDG_SHELL_CLIENT_PROTOCOL_XML}
#    )
#
#endif()


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   #_library.h
   buffer.cpp
   buffer.h
   cursor.cpp
   cursor.h
   #debug.cpp
   display.cpp
   display.h
   #display_xrender.cpp
   #enum_display_monitors.cpp
   framework.cpp
   framework.h
   #gdk_gdk.cpp
   #gdk_gdk.h
   icon.cpp
   icon.h
   gtk4_widget.cpp
   gtk4_widget.h

   keyboard.cpp
   keyboard.h
   #node.cpp
   #node.h
   #startupxxx-notification.cpp
   #startupxxx-notification.h
   text_composition_client.cpp
   text_composition_client.h
   #user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing.h
   #windowing_wm.cpp
   #windowing_gtk4.cpp

   #wayland_windowing.cpp
   #xfree86_key.h
   #xi.cpp
)

if (${HAS_WAYLAND})
   list(APPEND library_source
      ${XDG_SHELL_CLIENT_PROTOCOL_H}
      ${XDG_SHELL_CLIENT_PROTOCOL_C}
   )
endif ()


list(APPEND library_references
   acme
   acme_posix
   acme_windowing_g
   acme_windowing_gtk4
   #nano_user_x11
   #nano_user_gtk4
   apex
   apex_posix
   innate_ui_gtk4
   aqua
   aura
   aura_posix
   #aura_${OPERATING_SYSTEM_NAME}
   windowing_posix
   # windowing_system_wayland
   #windowing_system_x11

)


list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${library_source})

add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (${HAS_WAYLAND})
   list(APPEND WAYLAND_PKG_MODULES wayland-client wayland-protocols)
endif ()
if (${HAS_X11})
   list(APPEND X11_PKG_MODULES x11)
endif ()

if(${WIN32})
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   #add_dependencies(${PROJECT_NAME} draw2d_gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG xkbcommon x11 xrender xi xext libstartupxxx-notification-1.0 wayland-client wayland-server wayland-cursor)
   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk4 ${WAYLAND_PKG_MODULES} ${X11_PKG_MODULES} ${APPINDICATOR_PKG_MODULE})
   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gtk4 ${WAYLAND_PKG_MODULES} ${X11_PKG_MODULES} ${APPINDICATOR_PKG_MODULE})
   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gtk4 ${APPINDICATOR_PKG_MODULE})
   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk4 ${APPINDICATOR_PKG_MODULE})

   message(STATUS "windowing_gtk4 : APPINDICATOR_PKG_MODULE is \"${APPINDICATOR_PKG_MODULE}\"")

   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})

   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


   #add_dependencies(${PROJECT_NAME} draw2d_cairo)
   message(STATUS "PKGCONFIG at windowing_gtk4  gtk4 ${WAYLAND_PKG_MODULES} ${X11_PKG_MODULES} ${APPINDICATOR_PKG_MODULE}")
   message(STATUS "pkgconfig_cflags at windowing_gtk4  ${${PROJECT_NAME}_PKGCONFIG_CFLAGS}")
message(STATUS "libraries at windowing_gtk4  ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES}")

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/_operating_system/${SLASHED_OPERATING_SYSTEM}/include)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



