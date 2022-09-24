cmake_minimum_required(VERSION 3.16)
project(node_kde CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   copydesk.cpp
   copydesk.h
   desktop_environment.cpp
   desktop_environment.h
   display.cpp
   display.h
   enum_display_monitors.cpp
   _factory.cpp
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #gnome_direct.cpp
   #gtk_clipboard.cpp
   monitor.cpp
   monitor.h
   node.cpp
   node.h
   notify_icon.cpp
   notify_icon.h
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
   windowing_x11
   )


set_source_files_properties(q_node_impl.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(set_wallpaper.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(kde-open.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


add_library(node_kde SHARED ${library_source} set_wallpaper.cpp urlinfo.h kde-open.cpp)


target_precompile_headers(node_kde PRIVATE framework.h)


set_target_properties(node_kde PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(node_kde PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_kde PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   if(NOT DONT_USE_PKG_CONFIG)
      # dnf install qt5-qttools-devel qt5-qtx11extras-devel qt5-qttools-static
      pkg_check_modules(PKGCONFIG Qt5Core Qt5UiTools Qt5X11Extras)
   endif()
   target_compile_options(node_kde PRIVATE -fpermissive)
   target_compile_options(node_kde PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_kde PRIVATE ${PKGCONFIG_LDFLAGS})
   if(KDE_DESKTOP)
   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

   endif()
   #target_link_options(node_kde PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(node_kde PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   if(KDE_DESKTOP)
      target_link_libraries(node_kde PRIVATE KF5::Notifications)
      target_link_libraries(node_kde PRIVATE KF5::ConfigWidgets)
      target_link_libraries(node_kde PRIVATE KF5::IconThemes)
      target_link_libraries(node_kde PRIVATE KF5::KIOCore)
      target_link_libraries(node_kde PRIVATE KF5::KIOFileWidgets)
      target_link_libraries(node_kde PRIVATE KF5::KIOWidgets)
      target_link_libraries(node_kde PRIVATE KF5::KIONTLM)
      target_link_libraries(node_kde PRIVATE PW::KWorkspace)
   endif()
   target_link_options(node_kde PRIVATE -Wl,-z,defs)


endif ()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(node_kde PRIVATE _NODE_KDE_LIBRARY)



