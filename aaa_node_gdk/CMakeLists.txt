cmake_minimum_required(VERSION 3.16)
project(node_gdk CXX)


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        #_library.h
        #g_application.cpp
        #g_application.h
        #copydesk.cpp
        #copydesk.h
        desktop_environment.cpp
        desktop_environment.h
        #display.cpp
        #display.h
        framework.cpp
        framework.h
        #gconf.cpp
        gdk.h
        #gdk_part1.cpp
        gdk_part2.cpp
        gdk_part4.cpp
        #gtk_clipboard.cpp
        #gtk3_gtk3.cpp
        #gtk3_gtk3.h
        #gtk-launch.cpp
        monitor.cpp
        monitor.h
        node.cpp
        node.h
        #node_file_dialog.cpp
        #node_folder_dialog.cpp
        #    notify_icon.cpp
        #   notify_icon.h
        #windowing.cpp
        #windowing.h
        windowing_system.cpp
        windowing_system.h
        #x11_windowing_system.cpp
        #x11_windowing_system.h
)


if (${HAS_WAYLAND})
    list(APPEND library_source
            wayland_windowing_system.cpp
            wayland_windowing_system.h
    )

endif ()

if (NOT ${OPENBSD})

    list(APPEND library_source
            #appindicator.cpp
            #appindicator.h

    )

endif ()


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
)


    #if(${OPENBSD})
if (FALSE)
    list(APPEND library_references
            windowing_xcb
    )
else ()
    list(APPEND library_references
            windowing_x11
    )
endif ()

if (${HAS_WAYLAND})
    list(APPEND library_references
            windowing_system_wayland
            windowing_wayland
    )
endif ()

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${library_source})
#   os_context.h
#   os_context.cpp)
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
    #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


    #if(USE_PKGCONFIG)
    #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gconf-2.0 glib-2.0 gtk+-3.0 gdk-3.0)
    #   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0)
    #endif()
    if(${HAS_GTK4})
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk4 ${APPINDICATOR_PKG_MODULE})
        pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gtk4 ${APPINDICATOR_PKG_MODULE})
        else()
    pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 ${APPINDICATOR_PKG_MODULE})
    endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
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



