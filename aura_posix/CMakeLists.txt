cmake_minimum_required(VERSION 3.16)
project(aura_posix CXX)


list(APPEND library_source
        x11/desktop_environment.h
        x11/desktop_environment.cpp
        _.cpp
        _.h
        #_library.h
        appindicator.cpp
        appindicator.h
        _factory.cpp
        framework.cpp
        framework.h
        node.cpp
        node.h
        shell.cpp
        shell.h
        user_notify_icon_bridge.h
        )


list(APPEND library_references
        acme
        acme_posix
        apex
        apex_posix
        aqua
        aura
        )

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


if (WITH_X11 OR WITH_XCB)


    list(APPEND library_source
            x11/_.h
            x11/_.cpp
            x11/_constant.h
            #x11/keyboard.cpp
            #x11/keyboard.h
            x11/window.cpp
            x11/window.h
            x11/windowing.cpp
            x11/windowing.h
            )


    #   if(WITH_X11)

    list(APPEND library_source
            x11/display_lock.cpp
            x11/display_lock.h
            x11/startup-notification.cpp
            x11/startup-notification.h
            x11/xim_keyboard.cpp
            x11/xim_keyboard.h
            )

    #  endif()

endif ()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(aura_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(aura_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aura_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aura_posix PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(aura_posix PRIVATE ${library_references})


elseif (LINUX OR FREEBSD)


    list(APPEND extra_pkg_modules
            libstartup-notification-1.0
            )

    if (WITH_XCB)


        list(APPEND extra_pkg_modules
                x11 x11-xcb
                )


    else ()


        list(APPEND extra_pkg_modules
                x11
                )


    endif ()


    #if (USE_PKGCONFIG)
        pkg_check_modules(PKGCONFIG ${extra_pkg_modules})
    #endif ()


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(aura_posix PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} ${static_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(aura_posix PRIVATE _AURA_POSIX_LIBRARY)



