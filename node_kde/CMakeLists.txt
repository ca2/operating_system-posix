cmake_minimum_required(VERSION 3.17)
project(node_kde CXX)


list(APPEND node_kde_source
   _.cpp
   _.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   copydesk.cpp
   copydesk.h
   display.cpp
   display.h
   enum_display_monitors.cpp
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   gdk.cpp
   gdk.h
   gnome_direct.cpp
   gtk_clipboard.cpp
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
   windowing_xcb
   )


set_source_files_properties(q_node_impl.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


add_library(node_kde SHARED ${node_kde_source})

target_precompile_headers(node_kde PRIVATE framework.h)

set_target_properties(node_kde PROPERTIES LINKER_LANGUAGE CXX)




if (MSVC)
   target_compile_options(node_kde PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_kde PRIVATE ${library_references})
elseif (LINUX)
   pkg_check_modules(PKGCONFIG Qt5Core Qt5UiTools Qt5X11Extras)
   target_compile_options(node_kde PRIVATE -fpermissive)
   target_compile_options(node_kde PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_kde PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(node_kde PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(node_kde PRIVATE -Wl,-z,defs)
endif ()



target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_kde PRIVATE _NODE_KDE_LIBRARY)



