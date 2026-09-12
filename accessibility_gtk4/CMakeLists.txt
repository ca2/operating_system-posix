cmake_minimum_required(VERSION 3.17)
project(accessibility_gtk4 CXX)

project(accessibility_gtk4 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 QUIET IMPORTED_TARGET gtk4)

list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   #   _file.cpp
   #   _no_pch.cpp
   accessibility.cpp
   accessibility.h
   #   create_process.cpp
   #   create_process.h
   #   directory_system.cpp
   #   directory_system.h
   #   file_system.cpp
   #   file_system.h
   #   path_system.cpp
   #   path_system.h
   application.cpp
   application.h
   framework.cpp
   framework.h
   main_window.cpp
   main_window.h
   #message_loop.cpp
   #   mmresult.cpp
   #   mmresult.h
   #   mmsystem.cpp
   #   node.cpp
   #   node.h
   #   pipe.cpp
   #   pipe.h
   #process_control.cpp
   #process_control.h
   #   registry.cpp
   #   registry.h
   #   #sapi.cpp
   #   serial.cpp
   #   serial.h
   #   shared_memory.cpp
   #   shared_memory.h
   #   strdup_array.cpp
   #   trace.cpp
   #   uac_tools.cpp
   #   uac_tools.h
   #   windows_desktop.cpp
)

if(GTK4_FOUND)

   list(APPEND library_source
      gtk_accessible.cpp
      gtk_accessible.h
   )

endif()

add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

# The ca2 target names can be overridden by the parent build if needed.
set(
   ACCESSIBILITY_GTK4_CA2_LIBRARIES
   axis;acme
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

   #if(${USE_PKGCONFIG})
      #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    #  pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
   #endif()
   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE z ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

if(BUILD_TESTING AND UNIX)

   add_executable(accessibility_gtk4_process_control_test
      test/process_control.cpp)

   target_link_libraries(accessibility_gtk4_process_control_test PRIVATE
      static_accessibility_gtk4)

   add_test(NAME accessibility_gtk4_process_control_test
      COMMAND accessibility_gtk4_process_control_test)

endif()
