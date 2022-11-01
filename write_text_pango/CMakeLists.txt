cmake_minimum_required(VERSION 3.16)
project(write_text_pango CXX)


list(APPEND library_references
        acme
        apex
        aqua
        aura)


list(APPEND library_source
        _.cpp
        _.h
        #_write_text_pango.h
        _factory.cpp
    font_enumeration.cpp
    font_enumeration.h
    fonts.cpp
    fonts.h
        framework.cpp
        framework.h
        write_text.cpp
        write_text.h)


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(write_text_pango PRIVATE framework.h)

set_target_properties(write_text_pango PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


    target_compile_options(write_text_pango PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/write_text_pango.lib")
    target_link_options(write_text_pango PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/write_text_pango.def")
    target_link_libraries(write_text_pango PRIVATE acme apex aqua aura Gdiplus)


elseif(LINUX OR FREEBSD)


    if(NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG pangocairo)
    endif()
    target_compile_options(write_text_pango PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(write_text_pango PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(write_text_pango PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(write_text_pango PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(write_text_pango PRIVATE _WRITE_TEXT_PANGO_LIBRARY)



