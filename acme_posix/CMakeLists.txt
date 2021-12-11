cmake_minimum_required(VERSION 3.17)
project(acme_posix CXX)


list(APPEND library_source
   dbus/gsm_proxy.cpp
   _.cpp
   _.h
   _factory.cpp
   _process.cpp
   _acme_posix.h
   acme_dir.cpp
   acme_dir.h
   acme_file.cpp
   acme_file.h
   acme_path.cpp
   acme_path.h
   dbus.cpp
   file_memory_map.cpp
   file_memory_map.h
   framework.cpp
   framework.h
   node.cpp
   node.h
   pipe.cpp
   pipe.h
   process.cpp
   )


if(POSIX_LIST_SERIAL_PORTS)


   list(APPEND library_source posix/list_serial_ports.cpp)


endif()


if(INTERPROCESS_COMMUNICATION_SYSTEM_V)

   list(APPEND library_source
      system_v/interprocess_communication.cpp
      system_v/interprocess_communication.h
      )

endif()


add_library(acme_posix SHARED ${library_source})


if(POSIX_LIST_SERIAL_PORTS)

target_compile_definitions(acme_posix PRIVATE POSIX_LIST_SERIAL_PORTS)

endif()


if(POSIX_LIST_SERIAL_PORTS)

   target_compile_definitions(acme_posix PRIVATE INTERPROCESS_COMMUNICATION_SYSTEM_V)

endif()

list(APPEND library_references acme)


target_precompile_headers(acme_posix PRIVATE framework.h)


set_target_properties(acme_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(acme_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(acme_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(acme_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(acme_posix PRIVATE ${library_references})
   add_dependencies(acme_posix draw2d_gdiplus)


elseif(LINUX OR FREEBSD)


   pkg_check_modules(PKGCONFIG dbus-glib-1)
   target_compile_options(acme_posix PRIVATE -fpermissive)
   target_compile_options(acme_posix PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(acme_posix PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(acme_posix PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(acme_posix PRIVATE ${library_references})
   target_link_options(acme_posix PRIVATE -Wl,-z,defs)


endif ()


target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(acme_posix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(acme_posix PRIVATE _ACME_POSIX_LIBRARY)



