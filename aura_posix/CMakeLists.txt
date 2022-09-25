cmake_minimum_required(VERSION 3.16)
project(aura_posix CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   _factory.cpp
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


if(WITH_X11 OR WITH_XCB)


   list(APPEND library_source
           x11/_.h

           x11/_.cpp
      x11/_constant.h
      x11/window.cpp
      x11/window.h
      x11/windowing.cpp
      x11/windowing.h
   )


#   if(WITH_X11)

      list(APPEND library_source
      x11/display_lock.cpp
      x11/display_lock.h
     x11/startup-notification.cpp
     x11/startup-notification.h
      x11/xim_keyboard.cpp
      x11/xim_keyboard.h
         )

 #  endif()

endif()


add_library(aura_posix SHARED ${library_source} user_notify_icon_bridge.h x11/desktop_environment.h x11/desktop_environment.cpp)


target_precompile_headers(aura_posix PRIVATE framework.h)


set_target_properties(aura_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(aura_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(aura_posix PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   list(APPEND extra_pkg_modules
      libstartup-notification-1.0
      )

if(WITH_XCB)


   list(APPEND extra_pkg_modules
               x11 x11-xcb
      )


else()


   list(APPEND extra_pkg_modules
               x11
      )


endif()


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG ${extra_pkg_modules})
   endif()
   target_compile_options(aura_posix PRIVATE -fpermissive)
   target_compile_options(aura_posix PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(aura_posix PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(aura_posix PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(aura_posix PRIVATE ${library_references})
   target_link_options(aura_posix PRIVATE -Wl,-z,defs)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(aura_posix PRIVATE _AURA_POSIX_LIBRARY)



