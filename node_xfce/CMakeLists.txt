cmake_minimum_required(VERSION 3.17)
project(node_xfce CXX)


list(APPEND library_source
   _.cpp
   _.h
   _node_xfce.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   clipboard_data.h
   copydesk.cpp
   copydesk.h
   display.cpp
   display.h
   enum_display_monitors.cpp
   factory_exchange.cpp
   framework.cpp
   framework.h
   gdk.cpp
   gdk.h
   xfce_direct.cpp
   gtk_clipboard.cpp
   monitor.cpp
   monitor.h
   node.cpp
   node.h
   notify_icon.cpp
   windowing.cpp
   windowing.h
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   windowing_x11
   node_gtk
   )


add_library(node_xfce SHARED ${library_source} )

target_precompile_headers(node_xfce PRIVATE framework.h)

set_target_properties(node_xfce PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(node_xfce PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_xfce PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_xfce PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_xfce PRIVATE ${library_references})
   add_dependencies(node_xfce draw2d_gdiplus)
elseif (LINUX)
   pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator3-0.1)
   target_compile_options(node_xfce PRIVATE -fpermissive)
   target_compile_options(node_xfce PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_xfce PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(node_xfce PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(node_xfce PRIVATE -Wl,-z,defs)
endif ()


target_include_directories(node_xfce PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_xfce PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_xfce PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_xfce PRIVATE _NODE_XFCE_LIBRARY)


