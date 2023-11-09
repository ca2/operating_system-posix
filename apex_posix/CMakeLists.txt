cmake_minimum_required(VERSION 3.16)
project(apex_posix CXX)


list(APPEND library_source
        _.h
        _.cpp
        _factory.cpp
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
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (FILE_SYSTEM_INOTIFY)


    target_compile_definitions(apex_posix PRIVATE FILE_SYSTEM_INOTIFY)
    target_compile_definitions(static_apex_posix PRIVATE FILE_SYSTEM_INOTIFY)


endif ()


if (INTERPROCESS_COMMUNICATION_SYSTEM_5)

    target_compile_definitions(apex_posix PRIVATE INTERPROCESS_COMMUNICATION_SYSTEM_5)
    target_compile_definitions(static_apex_posix PRIVATE INTERPROCESS_COMMUNICATION_SYSTEM_5)

endif ()


if (POSIX_SPAWN)

    target_compile_definitions(apex_posix PRIVATE POSIX_SPAWN)
    target_compile_definitions(static_apex_posix PRIVATE POSIX_SPAWN)

endif ()


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(apex_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(apex_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(apex_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(apex_posix PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(apex_posix PRIVATE ${library_references})
    add_dependencies(apex_posix draw2d_gdiplus)


elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)



    if (FILE_SYSTEM_INOTIFY AND NOT DEFINED DEBIAN_LIKE AND NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG libinotify)
        target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
        target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
        target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
        target_link_libraries(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
    endif ()

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(apex_posix PRIVATE _APEX_POSIX_LIBRARY)



