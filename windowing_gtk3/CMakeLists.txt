cmake_minimum_required(VERSION 3.16)
project(windowing_gtk3 CXX)


list(APPEND library_source
   ../_startup_notification/_startup_notification.cpp
   ../_startup_notification/_startup_notification.h
   _.cpp
   _.h
   _factory.cpp
   #_library.h
   buffer.cpp
   buffer.h
   cursor.cpp
   cursor.h
   debug.cpp
   display.cpp
   display.h
   #display_xrender.cpp
   enum_display_monitors.cpp
   framework.cpp
   framework.h
   icon.cpp
   icon.h
   keyboard.cpp
   keyboard.h
   #node.cpp
   #node.h
   #startupxxx-notification.cpp
   #startupxxx-notification.h
   text_composition_client.cpp
   text_composition_client.h
   user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing_wm.cpp
   windowing_gtk3.cpp
   windowing.h
   wayland_windowing.cpp
   #xfree86_key.h
   xi.cpp
)


list(APPEND library_references
   acme
   acme_posix
   nano_graphics_cairo
   acme_windowing_g
   acme_windowing_gtk3
   apex
   apex_posix
   innate_ui_gtk3
   aqua
   aura
   aura_posix
   #aura_${OPERATING_SYSTEM_NAME}
   windowing_posix
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


if(${WIN32})
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   #add_dependencies(${PROJECT_NAME} draw2d_gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG xkbcommon x11 xrender xi xext libxxxstartupxxx-notification-1.0 wayland-client wayland-server wayland-cursor)
   list(APPEND extra_pkg_modules
      libstartup-notification-1.0
   )

   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 ${APPINDICATOR_PKG_MODULE} ${extra_pkg_modules})


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


endif ()


add_dependencies(${PROJECT_NAME}
   acme_windowing_gtk3
   innate_ui_gtk3
)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



