cmake_minimum_required(VERSION 3.17)
project(windowing_xcb CXX)


list(APPEND library_source
   _.cpp
   _.h
   _windowing_xcb.h
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
   display_xrender.cpp
   enum_display_monitors.cpp
   _factory.cpp
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
   #xcb_util.cpp
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


add_library(windowing_xcb SHARED ${library_source})

target_precompile_headers(windowing_xcb PRIVATE framework.h)

set_target_properties(windowing_xcb PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(windowing_xcb PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_xcb PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_xcb PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_xcb PRIVATE ${library_references})
elseif(LINUX OR FREEBSD)
   #pkg_check_modules

   # apt install libxcb-xinput-dev libxcb-image0-dev libxkbcommon-x11-dev

   pkg_check_modules(PKGCONFIG Qt5Core x11 xcb xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes)
   target_compile_options(windowing_xcb PRIVATE -fpermissive)
      target_compile_options(windowing_xcb PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(windowing_xcb PRIVATE ${PKGCONFIG_LDFLAGS})
   #target_link_options(windowing_xcb PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(windowing_xcb PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
   target_link_options(windowing_xcb PRIVATE -Wl,-z,defs)
endif ()




target_include_directories(windowing_xcb PRIVATE .)
target_include_directories(windowing_xcb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(windowing_xcb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(windowing_xcb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(windowing_xcb PRIVATE _WINDOWING_XCB_ALSA_LIBRARY)



