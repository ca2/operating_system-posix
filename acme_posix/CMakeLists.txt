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
        exclusive.cpp
        exclusive.h
        file.cpp
        file.h
        file_context.cpp
        file_context.h
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
        shmem.cpp
        shmem.h
        #stdio_file.cpp
        #stdio_file.h
        #process.cpp
)


if (POSIX_LIST_SERIAL_PORTS)


    list(APPEND library_source list_serial_ports.cpp)


endif ()


add_library(${PROJECT_NAME} SHARED ${library_source} process.cpp
   shmem.h
   shmem.cpp)
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (POSIX_LIST_SERIAL_PORTS)

    target_compile_definitions(${PROJECT_NAME} PRIVATE POSIX_LIST_SERIAL_PORTS)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE POSIX_LIST_SERIAL_PORTS)

endif ()


list(APPEND library_references acme)


list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(acme_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(acme_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(acme_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(acme_posix PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(acme_posix PRIVATE ${library_references})
    add_dependencies(acme_posix draw2d_gdiplus)


elseif (${LINUX} OR ${FREEBSD})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)



    #if (USE_PKGCONFIG)
    pkg_check_modules(PKGCONFIG dbus-glib-1)
    #endif ()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS} ${GLOBAL_EXTRA_COMPILER_FLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(acme_posix PRIVATE _ACME_POSIX_LIBRARY)



