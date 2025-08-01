cmake_minimum_required(VERSION 3.17)
project(innate_ui_gtk3 CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   button.cpp
   button.h
   framework.cpp
   framework.h
   dialog.cpp
   dialog.h
   icon.cpp
   icon.h
   innate_ui.cpp
   innate_ui.h
   still.cpp
   still.h
   window.cpp
   window.h
   )


list(APPEND library_references
   acme
   apex
)

add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE
       ${PROJECT_NAME}_common
       acme
       apex
       aqua
       aura
       Gdiplus
       Setupapi
       Credui)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    #if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    #endif()
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
    #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif()



target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
