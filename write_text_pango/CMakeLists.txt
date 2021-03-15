cmake_minimum_required(VERSION 3.17)
project(write_text_pango CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND write_text_pango_references
        acme
        apex
        aqua
        aura)


list(APPEND write_text_pango_source
        _.cpp
        _.h
        factory_exchange.cpp
        font_department.cpp
        font_department.h
        framework.cpp
        framework.h
        write_text.cpp
        write_text.h)


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(write_text_pango SHARED ${write_text_pango_source})

target_precompile_headers(write_text_pango PRIVATE framework.h)

set_target_properties(write_text_pango PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(write_text_pango PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/write_text_pango.lib")
    target_link_options(write_text_pango PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/write_text_pango.def")
    target_link_libraries(write_text_pango PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG pangocairo)
    target_compile_options(write_text_pango PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(write_text_pango PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(write_text_pango PRIVATE ${PKGCONFIG_LIBRARIES} ${write_text_pango_references})
    target_link_options(write_text_pango PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


#add_dependencies(write_text_pango ${app_common_dependencies} )


target_link_directories(write_text_pango PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(write_text_pango PRIVATE $ENV{HOME}/__config)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(write_text_pango PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(write_text_pango PRIVATE _WRITE_TEXT_PANGO_LIBRARY)
target_compile_definitions(write_text_pango PRIVATE UNICODE)
target_compile_definitions(write_text_pango PRIVATE _UNICODE)



