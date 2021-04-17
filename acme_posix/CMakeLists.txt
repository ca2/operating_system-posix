cmake_minimum_required(VERSION 3.17)
project(acme_posix CXX)


list(APPEND acme_posix_source
   _.h
   _process.cpp
   factory_exchange.cpp
   file_memory_map.cpp
   file_memory_map.h
   framework.cpp
   framework.h
   node.cpp
   node.h
   pipe.cpp
   pipe.h
   )


add_library(acme_posix SHARED ${acme_posix_source})

list(APPEND library_references acme)


target_precompile_headers(acme_posix PRIVATE framework.h)


set_target_properties(acme_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(acme_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(acme_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(acme_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(acme_posix PRIVATE ${library_references})
   add_dependencies(acme_posix draw2d_gdiplus)
elseif (LINUX)
   target_compile_options(acme_posix PRIVATE -fpermissive)
   target_compile_options(acme_posix PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(acme_posix PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(acme_posix PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
   target_link_options(acme_posix PRIVATE -Wl,-z,defs)
endif ()


target_include_directories(acme_posix PRIVATE .)
target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(acme_posix PRIVATE _ACME_POSIX_LIBRARY)



