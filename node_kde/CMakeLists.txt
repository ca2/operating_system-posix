cmake_minimum_required(VERSION 3.17)
project(node_kde CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
   set(LINUX TRUE)
   set(PLATFORM_NAME "linux")
   include(FindPkgConfig)
elseif (WIN32)
   set(PLATFORM_NAME "windows")
endif ()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND audio_alsa_source
   _.cpp
   _.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   clipboard_data.h
   copydesk.cpp
   copydesk.h
   enum_display_monitors.cpp
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   gdk.cpp
   gdk.h
   gnome_direct.cpp
   gtk_clipboard.cpp
   node.cpp
   node.h
   node_impl.cpp
   node_impl.h
   q_node_impl.cpp
   q_node_impl.h
   )


list(APPEND library_references
   acme
   node_ansios
   apex
   aqua
   aura
   node_linux
   windowing_xcb
   )


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


set_source_files_properties(q_node_impl.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)




add_library(node_kde SHARED ${audio_alsa_source})

target_precompile_headers(node_kde PRIVATE framework.h)

set_target_properties(node_kde PROPERTIES LINKER_LANGUAGE CXX)




if (MSVC)
   target_compile_options(node_kde PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_kde PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_kde PRIVATE ${library_references})
   add_dependencies(node_kde draw2d_gdiplus)
elseif (LINUX)
   pkg_check_modules(PKGCONFIG Qt5Core Qt5UiTools)
   target_compile_options(node_kde PRIVATE -fpermissive)
   target_compile_options(node_kde PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_kde PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(node_kde PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(node_kde PRIVATE asound)
   target_link_options(node_kde PRIVATE -Wl,-z,defs)
   add_dependencies(node_kde draw2d_cairo node_linux)
endif ()

add_dependencies(node_kde experience_core)


target_link_directories(node_kde PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(node_kde PRIVATE .)
target_include_directories(node_kde PRIVATE $ENV{HOME}/__config)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(node_kde PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_kde PRIVATE _MUSIC_MIDI_ALSA_LIBRARY)
target_compile_definitions(node_kde PRIVATE UNICODE)
target_compile_definitions(node_kde PRIVATE _UNICODE)



