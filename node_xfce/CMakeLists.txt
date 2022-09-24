cmake_minimum_required(VERSION 3.16)
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
   _factory.cpp
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
elseif(LINUX OR FREEBSD)


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 ${APPINDICATOR_PKG_MODULE})
   endif()
   target_compile_options(node_xfce PRIVATE -fpermissive)
      target_compile_options(node_xfce PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_xfce PRIVATE ${PKGCONFIG_LDFLAGS})
   #target_link_options(node_xfce PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(node_xfce PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(node_xfce PRIVATE -Wl,-z,defs)
endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(node_xfce PRIVATE _NODE_XFCE_LIBRARY)



