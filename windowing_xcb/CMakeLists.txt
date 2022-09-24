cmake_minimum_required(VERSION 3.16)
project(windowing_xcb CXX)


list(APPEND library_source
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
   display_xrender.cpp
   enum_display_monitors.cpp
   framework.cpp
   framework.h
   icon.cpp
   icon.h
   keyboard.cpp
   keyboard.h
   node.cpp
   node.h
   #startup-notification.cpp
   #startup-notification.h
   user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing_wm.cpp
   windowing_xcb.cpp
   windowing.h
   xcb_windowing.cpp
   text_composition_client.cpp 
   text_composition_client.h        
   xi.cpp
   windowing_xkb.cpp
   xcb_icccm.cpp
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   )


add_library(${PROJECT_NAME} SHARED ${library_source})


target_precompile_headers(windowing_xcb PRIVATE framework.h)


set_target_properties(windowing_xcb PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(windowing_xcb PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_xcb PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_xcb PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_xcb PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   if(NOT DONT_USE_PKG_CONFIG)
      #pkg_check_modules(PKGCONFIG libstartup-notification-1.0 Qt5Core x11 xcb xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes freetype2)
      pkg_check_modules(PKGCONFIG Qt5Core x11 xcb xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes freetype2)
   endif()
   target_compile_options(windowing_xcb PRIVATE -fpermissive)
   target_compile_options(windowing_xcb PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(windowing_xcb PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(windowing_xcb PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(windowing_xcb PRIVATE ${library_references})
   target_link_options(windowing_xcb PRIVATE -Wl,-z,defs)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(windowing_xcb PRIVATE _WINDOWING_XCB_LIBRARY)



