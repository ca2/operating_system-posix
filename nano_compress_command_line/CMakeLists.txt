cmake_minimum_required(VERSION 3.17)
project(nano_compress_command_line CXX)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${WIN32})
    set(LIBCXX_TARGETING_MSVC ON)
else ()
    set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        compress.cpp
        compress.h
        platform.cpp
        platform.h)


if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
   set(nano_target ${PROJECT_NAME})
   add_library(${nano_target} SHARED ${library_source})
   target_link_libraries(${nano_target} PRIVATE acme)
else()
   set(nano_target static_${PROJECT_NAME})
   add_library(${nano_target} STATIC ${library_source})
endif()

target_precompile_headers(${nano_target} PRIVATE platform.h)

#set_target_properties(${nano_target}} PROPERTIES LINKER_LANGUAGE CXX)


if(${WIN32})
    target_compile_options(${nano_target}} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${nano_target}} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${nano_target}} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${nano_target}}.lib")
    target_link_options(${nano_target}} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${nano_target}}.def")
    target_link_libraries(${nano_target}} PRIVATE acme apex aqua aura Gdiplus)
elseif (${LINUX})

    message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

endif ()


target_include_directories(${nano_target} PRIVATE $ENV{HOME}/__config)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(${nano_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${nano_target} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${nano_target} PRIVATE UNICODE)
target_compile_definitions(${nano_target} PRIVATE _UNICODE)
