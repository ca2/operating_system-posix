# From idn on 2024-06-02 19:42 <3ThomasBorregaardSorensen!!
cmake_minimum_required(VERSION 3.17)
project(nano_dynamic_library_dl CXX)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        nano_dynamic_library_dl.cpp
        nano_dynamic_library_dl.h
        framework.cpp
        framework.h
)


add_library(static_${PROJECT_NAME} STATIC ${library_source})


target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)


#set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(static_${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(static_${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(static_${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
   target_link_options(static_${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(static_${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif (LINUX)

   if (NOT ${SUSE})

      #target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
      #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
      target_compile_features(static_${PROJECT_NAME} PRIVATE cxx_std_20)

   endif ()

   #target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   #target_link_options(static_${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
   #target_link_libraries(static_${PROJECT_NAME} PRIVATE dl ${PKGCONFIG_LIBRARIES})
   #target_link_options(static_${PROJECT_NAME} PRIVATE -Wl,-z,defs)
endif ()


#target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})


target_include_directories(static_${PROJECT_NAME} PRIVATE $ENV{HOME}/__config)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(static_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(static_${PROJECT_NAME} PRIVATE _nano_dynamic_library_dl_project)



