cmake_minimum_required(VERSION 3.17)
project(accessibility_gtk4 LANGUAGES CXX)

find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
    pkg_check_modules(GTK4 QUIET IMPORTED_TARGET gtk4)
endif()

set(library_source
   _.cpp
   _.h
   _factory.cpp
   accessibility.cpp
   accessibility.h
   application.cpp
   application.h
   framework.cpp
   framework.h
   main_window.cpp
   main_window.h
   #process_control.cpp
   #process_control.h
)

if(GTK4_FOUND)

   list(APPEND library_source
      gtk_accessible.cpp
      gtk_accessible.h
   )

endif()

add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

# The ca2 target names can be overridden by the parent build if needed.
set(
   ACCESSIBILITY_GTK4_CA2_LIBRARIES
   axis;acme;accessibility_posix
   CACHE STRING
   "ca2 libraries linked by accessibility_gtk4"
)

function(configure_accessibility_gtk4_target target_name)

   target_compile_features(${target_name} PUBLIC cxx_std_17)

   target_precompile_headers(${target_name} PRIVATE framework.h)

   target_include_directories(${target_name} PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/../..
      ${CMAKE_CURRENT_SOURCE_DIR}/..
      ${CMAKE_CURRENT_SOURCE_DIR}
   )

   target_link_libraries(${target_name} PRIVATE
      ${ACCESSIBILITY_GTK4_CA2_LIBRARIES}
   )

   if(GTK4_FOUND)

      target_link_libraries(${target_name} PRIVATE PkgConfig::GTK4)

   endif()

   set_target_properties(${target_name} PROPERTIES
      LINKER_LANGUAGE CXX
      POSITION_INDEPENDENT_CODE ON
   )

endfunction()

configure_accessibility_gtk4_target(${PROJECT_NAME})
configure_accessibility_gtk4_target(static_${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE _accessibility_gtk4_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE
   _accessibility_gtk4_project
   CUBE
)

if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")

   target_link_options(${PROJECT_NAME} PRIVATE
      "-Wl,-rpath,\$ORIGIN"
      "-Wl,-z,defs"
   )

endif()

if(BUILD_TESTING AND UNIX)

   add_executable(accessibility_gtk4_process_control_test
      test/process_control.cpp
      process_control.cpp)

   target_link_libraries(accessibility_gtk4_process_control_test PRIVATE
      static_acme)

   add_test(NAME accessibility_gtk4_process_control_test
      COMMAND accessibility_gtk4_process_control_test)

endif()






list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})




target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
#target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
