cmake_minimum_required(VERSION 3.16)
project(acme_posix CXX)


list(APPEND library_source
        dbus/gsm_proxy.cpp
        _.cpp
        _.h
        _factory.cpp
        #_process.cpp
        #_acme_posix.h
        acme_directory.cpp
        acme_directory.h
        acme_file.cpp
        acme_file.h
        acme_path.cpp
        acme_path.h
        dbus.cpp
        exception_translator.cpp
        exception_translator.h
        file_memory_map.cpp
        file_memory_map.h
        framework.cpp
        framework.h
        mutex.cpp
        mutex.h
        node.cpp
        node.h
        pipe.cpp
        pipe.h
        #stdio_file.cpp
        #stdio_file.h
        #process.cpp
        )


if (POSIX_LIST_SERIAL_PORTS)


    list(APPEND library_source list_serial_ports.cpp)


endif ()


add_library(${PROJECT_NAME} SHARED ${library_source} exclusive.cpp exclusive.h)


if (POSIX_LIST_SERIAL_PORTS)

    target_compile_definitions(acme_posix PRIVATE POSIX_LIST_SERIAL_PORTS)

endif ()


list(APPEND library_references acme)


target_precompile_headers(acme_posix PRIVATE framework.h)


set_target_properties(acme_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(acme_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(acme_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(acme_posix PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(acme_posix PRIVATE ${library_references})
    add_dependencies(acme_posix draw2d_gdiplus)


elseif (LINUX OR FREEBSD)


    if (NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG dbus-glib-1)
    endif ()
    target_compile_options(acme_posix PRIVATE -fpermissive)
    target_compile_options(acme_posix PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(acme_posix PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(acme_posix PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(acme_posix PRIVATE ${library_references})
    target_link_options(acme_posix PRIVATE -Wl,-z,defs)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(acme_posix PRIVATE _ACME_POSIX_LIBRARY)



