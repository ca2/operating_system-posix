cmake_minimum_required(VERSION 3.16)
project(node_gtk CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   #_library.h
   application.cpp
   application.h
   desktop_environment.cpp
   desktop_environment.h
   display.cpp
   display.h
   framework.cpp
   framework.h
   gconf.cpp
   gdk_gdk.cpp
   gdk_gdk.h
   gtk_gtk.cpp
   gtk_gtk.h
   gtk-launch.cpp
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


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   #if(NOT DONT_USE_PKG_CONFIG)
      #pkg_check_modules(PKGCONFIG gconf-2.0 glib-2.0 gtk+-3.0 gdk-3.0)
      pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0)
   #endif()
   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _NODE_GTK_LIBRARY)



