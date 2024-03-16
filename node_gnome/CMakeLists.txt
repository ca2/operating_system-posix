cmake_minimum_required(VERSION 3.16)
project(node_gnome CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   clipboard_data.h
   copydesk.cpp
   copydesk.h
   desktop_environment.cpp
   desktop_environment.h
   display.cpp
   display.h
   enum_display_monitors.cpp
   _factory.cpp
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #gnome_direct.cpp
   gtk_clipboard.cpp
   monitor.cpp
   monitor.h
   node.cpp
   node.h
   notify_icon.cpp
   windowing.cpp
   windowing.h
   )



list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   windowing_x11
   )

if(${HAS_GTK4})
    list(APPEND library_references node_gtk4)
elseif(${HAS_GTK3})
    list(APPEND library_references node_gtk3)
endif()

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


#
#if(${DISTRO} STREQUAL "raspbian")
#
#   set(APPINDICATOR_PKG_MODULE "ayatana-appindicator3-0.1")
#
#   add_compile_definitions(AYATANA_APPINDICATOR)
#
#elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#
#   message(STATUS "DISTRO is ${DISTRO}")
#
#   if("${DISTRO}" STREQUAL "ubuntu")
#
#      #set(APPINDICATOR_PKG_MODULE "appindicator3-0.1")
#
#      set(APPINDICATOR_PKG_MODULE "ayatana-appindicator3-0.1")
#
#      add_compile_definitions(AYATANA_APPINDICATOR)
#
#   elseif(${DISTRO} STREQUAL "debian")
#
#      add_compile_definitions(AYATANA_APPINDICATOR)
#
#      set(APPINDICATOR_PKG_MODULE "ayatana-appindicator3-0.1")
#
#   else()
#
#      set(APPINDICATOR_PKG_MODULE "appindicator3-0.1")
#
#   endif()
#
#elseif(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
#
#    add_compile_definitions(AYATANA_APPINDICATOR)
#
#    set(APPINDICATOR_PKG_MODULE "ayatana-appindicator3-0.1")
#
#endif()
#


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})


elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})

   if(${HAS_GTK4})
      pkg_check_modules(PKGCONFIG x11 glib-2.0 gtk4 gdk-3.0 ${APPINDICATOR_PKG_MODULE})
   elseif(${HAS_GTK3})
       pkg_check_modules(PKGCONFIG x11 glib-2.0 gtk+-3.0 gdk-3.0 ${APPINDICATOR_PKG_MODULE})
   endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE  ${library_references} ${PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _NODE_GNOME_LIBRARY)



