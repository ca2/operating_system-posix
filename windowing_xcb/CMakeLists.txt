cmake_minimum_required(VERSION 3.16)
project(windowing_xcb CXX)


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        #_library.h
        buffer.cpp
        buffer.h
        cursor.cpp
        cursor.h
        debug.cpp
        display.cpp
        display.h
        display_xrender.cpp
        enum_display_monitors.cpp
        framework.cpp
        framework.h
        icon.cpp
        icon.h
        keyboard.cpp
        keyboard.h
        #node.cpp
        #node.h
        #startup-notification.cpp
        #startup-notification.h
        user.cpp
        window.cpp
        window.h
        windowing.cpp
        windowing_wm.cpp
        windowing_xcb.cpp
        windowing.h
        xcb_windowing.cpp
        text_composition_client.cpp
        text_composition_client.h
        xi.cpp
        windowing_xkb.cpp
        xcb_icccm.cpp
)


list(APPEND library_references
        acme
        acme_posix
        apex
        apex_posix
        aqua
        aura
        aura_posix
        windowing_posix
        windowing_system_x11
        windowing_system_xcb
        nano_user_x11
        nano_user_xcb
)

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(windowing_xcb PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(windowing_xcb PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(windowing_xcb PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(windowing_xcb PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(windowing_xcb PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


    if (${USE_PKGCONFIG})
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG libstartup-notification-1.0 Qt5Core x11 xcb xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes freetype2)
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG Qt5Core x11 xcb xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes freetype2)
        pkg_check_modules(${PROJECT_NAME}_PKGCONFIG x11 xcb xcb-shm xcb-sync xcb-xkb xcb-icccm xcb-xinput xcb-aux x11-xcb xcb-render xcb-image xkbcommon-x11 xcb-xfixes freetype2)
    endif ()
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
    target_link_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



