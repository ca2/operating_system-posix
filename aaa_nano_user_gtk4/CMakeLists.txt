cmake_minimum_required(VERSION 3.17)
project(nano_user_gtk4 CXX)


message(STATUS "Project: nano_user_gtk4")


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else ()
    set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
   _gtk4.h
        #_user.cpp
        #device.cpp
        #device.h
        display.cpp
        display.h
        display_base.cpp
        display_base.h
        framework.cpp
        framework.h
   gtk4.cpp
   SubclassedModelButton.cpp
   SubclassedModelButton.h
        window.cpp
        window.h
        #window_base.cpp
        #window_base.h
        #wayland-gtk_shell1.c
        #wayland-gtk_shell1.h
        #wayland-xdg_activation_v1.c
        #wayland-xdg_activation_v1.h
        #wayland-xdg_wm_base.c
        #wayland-xdg_wm_base.h
)

add_library(${PROJECT_NAME} SHARED ${library_source}
   #icon.cpp
   #icon.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
#set_source_files_properties(wayland-gtk_shell1.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
#set_source_files_properties(wayland-xdg_activation_v1.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
#set_source_files_properties(wayland-xdg_wm_base.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

list(APPEND library_references
        acme
        windowing_system_gtk4
        #nano_user_cairo
)

if(${HAS_X11})

    list(APPEND library_references
       nano_user_x11
    )

endif()


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG cairo xkbcommon wayland-cursor wayland-client wayland-server)
    pkg_check_modules(${PROJECT_NAME}_PKGCONFIG cairo gtk4)
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
    #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif ()

add_dependencies(${PROJECT_NAME} ${library_references} ${global_library_references})

target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


target_include_directories(${PROJECT_NAME} PRIVATE $ENV{HOME}/__config)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)
