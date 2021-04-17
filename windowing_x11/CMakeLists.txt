cmake_minimum_required(VERSION 3.17)
project(windowing_x11 CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")




set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND audio_alsa_source
   _.h
   _.cpp
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
   display_lock.cpp
   display_lock.h
   display_xrender.cpp
   enum_display_monitors.cpp
   factory_exchange.cpp
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
   #node.cpp
   #node.h
   sn.cpp
   sn.h
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
   apex
   aqua
   aura
   aura_linux
   )


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(windowing_x11 SHARED ${audio_alsa_source})

target_precompile_headers(windowing_x11 PRIVATE framework.h)

set_target_properties(windowing_x11 PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(windowing_x11 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(windowing_x11 PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(windowing_x11 PRIVATE ${library_references})
   add_dependencies(windowing_x11 draw2d_gdiplus)
elseif (LINUX)
   pkg_check_modules(PKGCONFIG x11 xrender xi)
   target_compile_options(windowing_x11 PRIVATE -fpermissive)
   target_compile_options(windowing_x11 PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(windowing_x11 PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(windowing_x11 PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
   target_link_libraries(windowing_x11 PRIVATE asound)
   target_link_options(windowing_x11 PRIVATE -Wl,-z,defs)
   add_dependencies(windowing_x11 draw2d_cairo)
endif ()


#add_dependencies(windowing_x11 experience_core)


target_link_directories(windowing_x11 PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(windowing_x11 PRIVATE .)
target_include_directories(windowing_x11 PRIVATE $ENV{HOME}/__config)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(windowing_x11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(windowing_x11 PRIVATE _MUSIC_MIDI_ALSA_LIBRARY)
target_compile_definitions(windowing_x11 PRIVATE UNICODE)
target_compile_definitions(windowing_x11 PRIVATE _UNICODE)



