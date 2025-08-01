cmake_minimum_required(VERSION 3.16)
project(node_xfce CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_node_xfce.h
   #appindicator.cpp
   #appindicator.h
   #application.cpp
   #application.h
   #clipboard_data.h
   #copydesk.cpp
   #copydesk.h
   #display.cpp
   #display.h
   enum_display_monitors.cpp
   _factory.cpp
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #xfce_direct.cpp
   #gtk_clipboard.cpp
   #monitor.cpp
   #monitor.h
   node.cpp
   node.h
   #notify_icon.cpp
   #windowing.cpp
   #windowing.h
   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   #windowing_x11
   node_gtk3
   )


add_library(${PROJECT_NAME} ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(node_xfce PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(node_xfce PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_xfce PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_xfce PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_xfce PRIVATE ${library_references} ${global_library_references})
   add_dependencies(node_xfce draw2d_gdiplus)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   if(USE_PKGCONFIG)
      pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 ${APPINDICATOR_PKG_MODULE})
   endif()


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_link_options(node_xfce PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   
   target_link_libraries(node_xfce PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



