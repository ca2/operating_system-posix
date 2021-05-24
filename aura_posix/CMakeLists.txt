cmake_minimum_required(VERSION 3.17)
project(aura_posix CXX)


list(APPEND aura_posix_source
   _.cpp
   _.h
   _aura_posix.h
   appindicator.cpp
   appindicator.h
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   node.cpp
   node.h
   shell.cpp
   shell.h
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   )


if(WITH_X11)


   list(APPEND aura_posix_source
      x11/_.cpp
      x11/_const.h
      x11/display_lock.cpp
      x11/display_lock.h
      x11/window.cpp
      x11/window.h
      x11/windowing.cpp
      x11/windowing.h
      x11/xim_keyboard.cpp
      x11/xim_keyboard.h
      )


endif()


add_library(aura_posix SHARED ${aura_posix_source} x11/_x11.h)


target_precompile_headers(aura_posix PRIVATE framework.h)


set_target_properties(aura_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(aura_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(aura_posix PRIVATE ${library_references})


elseif (LINUX)


   #pkg_check_modules(PKGCONFIG x11 x11-xcb)
   pkg_check_modules(PKGCONFIG x11)
   target_compile_options(aura_posix PRIVATE -fpermissive)
   target_compile_options(aura_posix PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(aura_posix PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(aura_posix PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(aura_posix PRIVATE -Wl,-z,defs)


endif ()


target_include_directories(aura_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(aura_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(aura_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aura_posix PRIVATE _AURA_POSIX_LIBRARY)



