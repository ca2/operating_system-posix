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
   platform.cpp
   platform.h
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

if(GTK4_FOUND)

   target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::GTK4)
   target_link_libraries(static_${PROJECT_NAME} PUBLIC PkgConfig::GTK4)

endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

# The ca2 target names can be overridden by the parent build if needed.
list(APPEND
   library_references
   axis
   acme
   accessibility_posix
)


#function(configure_accessibility_gtk4_target target_name)

   #target_compile_features(${target_name} PUBLIC cxx_std_17)


   target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)

   target_include_directories(${PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/../..
      ${CMAKE_CURRENT_SOURCE_DIR}/..
      ${CMAKE_CURRENT_SOURCE_DIR}
   )


   set_target_properties(${PROJECT_NAME} PROPERTIES
      LINKER_LANGUAGE CXX
      POSITION_INDEPENDENT_CODE ON
   )

#endfunction()


target_compile_definitions(${PROJECT_NAME} PRIVATE _accessibility_gtk4_project)


if(${LINUX} OR ${__BSD__})

   #if(${USE_PKGCONFIG})
      #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    #  pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
   #endif()




   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG gtk4)
   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
   target_link_libraries(${PROJECT_NAME} PRIVATE  ${library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)



   #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)


   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

if(BUILD_TESTING AND UNIX)

   add_executable(accessibility_gtk4_process_control_test
      test/process_control.cpp)

   target_link_libraries(${PROJECT_NAME} PRIVATE
      static_accessibility_gtk4)

   add_test(NAME accessibility_gtk4_process_control_test
      COMMAND accessibility_gtk4_process_control_test)

endif()
