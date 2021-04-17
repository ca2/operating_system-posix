cmake_minimum_required(VERSION 3.17)
project(apex_posix CXX)


list(APPEND apex_posix_source
   _.h
   _.cpp
   datetime.cpp
   datetime.h
   factory_exchange.cpp
   file_os_watcher.cpp
   file_os_watcher.h
   framework.cpp
   framework.h
   #application.cpp
   #application.h
   node.cpp
   node.h
   system_color.cpp
   system_time.cpp
   )


list(APPEND library_references acme acme_posix apex)


add_library(apex_posix SHARED ${apex_posix_source})

target_precompile_headers(apex_posix PRIVATE framework.h)

set_target_properties(apex_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(apex_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(apex_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(apex_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(apex_posix PRIVATE ${library_references})
   add_dependencies(apex_posix draw2d_gdiplus)
elseif (LINUX)
   target_compile_options(apex_posix PRIVATE -fpermissive)
   target_compile_options(apex_posix PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(apex_posix PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(apex_posix PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   #target_link_libraries(apex_posix PRIVATE asound)
   target_link_options(apex_posix PRIVATE -Wl,-z,defs)
endif ()


target_include_directories(apex_posix PRIVATE .)
target_include_directories(apex_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(apex_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(apex_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(apex_posix PRIVATE _APEX_POSIX_LIBRARY)



