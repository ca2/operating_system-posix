cmake_minimum_required(VERSION 3.17)
project(node_gtk CXX)


list(APPEND library_source
   _.cpp
   _.h
   _node_gtk.h
   #appindicator.cpp
   #appindicator.h
   application.cpp
   application.h
   #clipboard_data.h
   #copydesk.cpp
   #copydesk.h
   display.cpp
   display.h
   #enum_display_monitors.cpp
   _factory.cpp
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #gnome_direct.cpp
   #gtk_direct2.cpp
   #gtk_clipboard.cpp
   monitor.cpp
   monitor.h
   node.cpp
   node.h
   #notify_icon.cpp
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
   )


add_library(node_gtk SHARED ${library_source} )

target_precompile_headers(node_gtk PRIVATE framework.h)

set_target_properties(node_gtk PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(node_gtk PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_gtk PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_gtk PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_gtk PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator3-0.1)
   target_compile_options(node_gtk PRIVATE -fpermissive)
   target_compile_options(node_gtk PRIVATE ${PKGCONFIG_CFLAGS})
   #target_link_options(node_gtk PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(node_gtk PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(node_gtk PRIVATE -Wl,-z,defs)


endif ()


target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_gtk PRIVATE _NODE_GTK_LIBRARY)



