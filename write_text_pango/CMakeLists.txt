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
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(write_text_pango PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


    target_compile_options(write_text_pango PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_pango PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/write_text_pango.lib")
    target_link_options(write_text_pango PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/write_text_pango.def")
    target_link_libraries(write_text_pango PRIVATE acme apex aqua aura Gdiplus)


elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})


    if(USE_PKGCONFIG)
        pkg_check_modules(PKGCONFIG pangocairo)
    endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(write_text_pango PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(write_text_pango PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "(2) PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(write_text_pango PRIVATE _WRITE_TEXT_PANGO_LIBRARY)



