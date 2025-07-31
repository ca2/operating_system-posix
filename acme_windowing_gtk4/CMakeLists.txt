cmake_minimum_required(VERSION 3.17)
project(acme_windowing_gtk4 CXX)


message(STATUS "Project: ${PROJECT_NAME}")


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else ()
    set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
        _.cpp
        _.h
        _gtk4.h
        _factory.cpp
        display.cpp
        display.h
        #display_base.cpp
        #display_base.h
        framework.cpp
        framework.h
        #gdk_gdk.cpp
        #gdk_gdk.h
        gtk4.cpp
        keyboard.h
        #SubclassedGizmo.cpp
        #SubclassedGizmo.h
        SubclassedModelButton.cpp
        SubclassedModelButton.h
        #xkb_input.cpp
        #xkb_input.h
        window.cpp
        window.h
        windowing.cpp
        windowing.h
)


list(APPEND library_references
   acme
   acme_windowing_g
)



add_library(${PROJECT_NAME} SHARED ${library_source})
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)

   #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG cairo xkbcommon wayland-client wayland-server wayland-cursor)
   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gtk4)
   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
    
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   
   target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)

   message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})


endif ()


add_dependencies(${PROJECT_NAME} acme acme_windowing_g)

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
