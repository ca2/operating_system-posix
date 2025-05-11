cmake_minimum_required(VERSION 3.16)
project(windowing_q6 CXX)


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
   gdk_gdk.cpp
   gdk_gdk.h
   icon.cpp
   icon.h
   keyboard.cpp
   keyboard.h
   #node.cpp
   #node.h
   #startupxxx-notification.cpp
   #startupxxx-notification.h
   #text_composition_client.cpp
   #text_composition_client.h
   #user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing.h
   #windowing_wm.cpp
   #windowing_kde5.cpp

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
   acme_windowing_q
   acme_windowing_q6
   nano_graphics_cairo
   apex
   apex_posix
   innate_ui_q
   innate_ui_q6
   aqua
   aura
   aura_posix
   windowing_posix
   windowing_q
   #aura_${OPERATING_SYSTEM_NAME}
   #windowing_q6
   # windowing_system_wayland
   #windowing_system_x11
   #nano_user_wayland
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

#if(${HAS_WAYLAND})
#    list(APPEND WAYLAND_PKG_MODULES wayland-client wayland-protocols)
#endif()
#if(${HAS_X11})
#    list(APPEND X11_PKG_MODULES x11)
#endif()


if (${HAS_Q6})

   list(APPEND system_libraries
      Qt6::Core
      Qt6::Widgets
   )

elseif (${HAS_KDE5})

   list(APPEND system_libraries
      Qt5::Core
      Qt5::Widgets
   )

endif ()


if (MSVC)
   target_compile_options(windowing_wayland PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_wayland PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_wayland PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_wayland PRIVATE ${library_references} ${global_library_references})
   #add_dependencies(windowing_wayland draw2d_gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   #pkg_check_modules(PKGCONFIG xkbcommon x11 xrender xi xext libstartupx-notification-1.0 wayland-client wayland-server wayland-cursor)
   #pkg_check_modules(PKGCONFIG ${WAYLAND_PKG_MODULES} ${X11_PKG_MODULES} ${APPINDICATOR_PKG_MODULE})

   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})

   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${system_libraries} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${system_libraries} ${PKGCONFIG_LIBRARIES} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


   #add_dependencies(windowing_wayland draw2d_cairo)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/_operating_system/${SLASHED_OPERATING_SYSTEM}/include)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE $ENV{HOME}/__config)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



