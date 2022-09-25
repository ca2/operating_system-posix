cmake_minimum_required(VERSION 3.16)
project(windowing_x11 CXX)


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
   startup-notification.cpp
   startup-notification.h
   text_composition_client.cpp
   text_composition_client.h
   user.cpp
   window.cpp
   window.h
   windowing.cpp
   windowing_wm.cpp
   windowing_x11.cpp
   windowing.h
   x11_windowing.cpp
   xi.cpp
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   aura_${OPERATING_SYSTEM_NAME}
   )


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(windowing_x11 PRIVATE framework.h)

set_target_properties(windowing_x11 PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(windowing_x11 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_x11 PRIVATE ${library_references})
   #add_dependencies(windowing_x11 draw2d_gdiplus)
elseif(LINUX OR FREEBSD)


#   if(UBUNTU)
#      list(APPEND library_references
#         X11
#         Xrender)
#   endif()

   pkg_check_modules(PKGCONFIG x11 xrender xi)
   target_compile_options(windowing_x11 PRIVATE -fpermissive)
   target_compile_options(windowing_x11 PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(windowing_x11 PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(windowing_x11 PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(windowing_x11 PRIVATE ${library_references})
   target_link_options(windowing_x11 PRIVATE -Wl,-z,defs)
   #add_dependencies(windowing_x11 draw2d_cairo)

endif ()


#list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(windowing_x11 PRIVATE _WINDOWING_X11_LIBRARY)



