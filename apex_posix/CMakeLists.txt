cmake_minimum_required(VERSION 3.16)
project(apex_posix CXX)


list(APPEND library_source
        _.h
        _.cpp
        _factory.cpp
        file_context.cpp
        file_context.h
        framework.cpp
        framework.h
        node.cpp
        node.h
        os_context.cpp
        os_context.h
        #system_color.cpp
        #system_time.cpp
        )


if (FILE_SYSTEM_INOTIFY)


    list(APPEND library_source
            inotify/watcher.cpp
            inotify/watcher.h
            inotify/watch.cpp
            inotify/watch.h
            )


endif ()


if (INTERPROCESS_COMMUNICATION_SYSTEM_5)

    list(APPEND library_source
            system_5/interprocess_base.cpp
            system_5/interprocess_base.h
            system_5/interprocess_caller.cpp
            system_5/interprocess_caller.h
            system_5/interprocess_target.cpp
            system_5/interprocess_target.h
            )

endif ()


if (POSIX_SPAWN)


    list(APPEND library_source
            posix_spawn/process.cpp
            posix_spawn/process.h)


endif ()


list(APPEND library_references acme acme_posix apex)


add_library(${PROJECT_NAME} SHARED ${library_source})


if (FILE_SYSTEM_INOTIFY)


    target_compile_definitions(apex_posix PRIVATE FILE_SYSTEM_INOTIFY)


endif ()


if (INTERPROCESS_COMMUNICATION_SYSTEM_5)

    target_compile_definitions(apex_posix PRIVATE INTERPROCESS_COMMUNICATION_SYSTEM_5)

endif ()


if (POSIX_SPAWN)

    target_compile_definitions(apex_posix PRIVATE POSIX_SPAWN)

endif ()


target_precompile_headers(apex_posix PRIVATE framework.h)


set_target_properties(apex_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(apex_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(apex_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(apex_posix PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(apex_posix PRIVATE ${library_references})
    add_dependencies(apex_posix draw2d_gdiplus)


elseif (LINUX OR FREEBSD)


    if (FILE_SYSTEM_INOTIFY AND NOT DEFINED DEBIAN_LIKE AND NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG libinotify)
        target_compile_options(apex_posix PRIVATE ${PKGCONFIG_CFLAGS})
        target_link_options(apex_posix PRIVATE ${PKGCONFIG_LDFLAGS})
        target_link_libraries(apex_posix PRIVATE ${PKGCONFIG_LIBRARIES})
    endif ()

    target_compile_options(apex_posix PRIVATE -fpermissive)
    target_link_libraries(apex_posix PRIVATE ${library_references})
    target_link_options(apex_posix PRIVATE -Wl,-z,defs)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(apex_posix PRIVATE _APEX_POSIX_LIBRARY)



