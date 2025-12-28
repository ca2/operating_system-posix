cmake_minimum_required(VERSION 3.17)
project(innate_ui_kde5 CXX)


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


if(${HAS_KDE6})

    list(APPEND system_libraries
            Qt6::Core
            Qt6::Widgets
    )

elseif(${HAS_KDE5})

    list(APPEND system_libraries
            Qt5::Core
            Qt5::Widgets
    )

endif()


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${WIN32})
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
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 freetype2 kdexxx5)
        pkg_check_modules(${PROJECT_NAME}_PKGCONFIG freetype2)
    #endif()
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
    #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${system_libraries} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif()



target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
