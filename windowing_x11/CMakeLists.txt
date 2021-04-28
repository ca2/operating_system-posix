cmake_minimum_required(VERSION 3.17)
project(windowing_x11 CXX)


list(APPEND windowing_x11_source
   _.h
   _.cpp
   #application.cpp
   #application.h
   buffer.cpp
   buffer.h
   cursor.cpp
   cursor.h
   #copydesk.cpp
   #copydesk.h
   debug.cpp
   display.cpp
   display.h
   ../aura_posix/display_lock.cpp
   ../aura_posix/display_lock.h
   display_xrender.cpp
   enum_display_monitors.cpp
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #gnome_direct.cpp
   icon.cpp
   icon.h
   keyboard.cpp
   keyboard.h
   node.cpp
   node.h
   sn.cpp
   sn.h
   text_composition_client.cpp
   text_composition_client.h
   user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing_wm.cpp
   windowing_x11.cpp
   windowing.h
   x11_windowing.cpp
   xi.cpp
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   aura_linux
   )


add_library(windowing_x11 SHARED ${windowing_x11_source})

target_precompile_headers(windowing_x11 PRIVATE framework.h)

set_target_properties(windowing_x11 PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(windowing_x11 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_x11 PRIVATE ${library_references})
   add_dependencies(windowing_x11 draw2d_gdiplus)
elseif (LINUX)
   pkg_check_modules(PKGCONFIG x11 xrender xi)
   target_compile_options(windowing_x11 PRIVATE -fpermissive)
   target_compile_options(windowing_x11 PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(windowing_x11 PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(windowing_x11 PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
   target_link_options(windowing_x11 PRIVATE -Wl,-z,defs)
   add_dependencies(windowing_x11 draw2d_cairo)
endif ()


target_include_directories(windowing_x11 PRIVATE .)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(windowing_x11 PRIVATE _WINDOWING_X11_ALSA_LIBRARY)



