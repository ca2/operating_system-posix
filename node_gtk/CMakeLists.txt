cmake_minimum_required(VERSION 3.17)
project(node_gtk CXX)


list(APPEND library_source
   _.cpp
   _.h
   _node_gtk.h
   application.cpp
   application.h
   display.cpp
   display.h
   _factory.cpp
   framework.cpp
   framework.h
   gconf.cpp
   gdk_gdk.cpp
   gdk_gdk.h
   gtk_gtk.cpp
   gtk_gtk.h
   monitor.cpp
   monitor.h
   node.cpp
   node.h
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


add_library(node_gtk SHARED ${library_source})

target_precompile_headers(node_gtk PRIVATE framework.h)

set_target_properties(node_gtk PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(node_gtk PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_gtk PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_gtk PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_gtk PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   pkg_check_modules(PKGCONFIG gconf-2.0 glib-2.0 gtk+-3.0 gdk-3.0 appindicator3-0.1)
   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif ()


target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_gtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_gtk PRIVATE _NODE_GTK_LIBRARY)



