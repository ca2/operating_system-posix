cmake_minimum_required(VERSION 3.16)
project(common_kde CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   framework.cpp
   framework.h
   #activation_token.cpp
   #activation_token.h
   #gdk_3_and_4.cpp
   #gdk_3_and_4.h
   kde_5_and_6.cpp
   kde_5_and_6.h

)


list(APPEND library_references
   acme
)


list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)

if(${HAS_KDE6})

   list(APPEND this_system_libraries
      Qt6::Core
      Qt6::Widgets
   )

elseif(${HAS_KDE5})

   list(APPEND this_system_libraries
      Qt5::Core
      Qt5::Widgets
   )

endif()


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
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


   #if(USE_PKGCONFIG)
   #pkg_check_modules(PKGCONFIG gconf-2.0 glib-2.0 gtk+-3.0 gdk-3.0)
   #   pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0)
   #endif()
#   if (${HAS_GTK4})
#      pkg_check_modules(PKGCONFIG gtk4 dbus-1)
#   elseif (${HAS_GTK3})
#      pkg_check_modules(PKGCONFIG gtk+-3.0 dbus-1)
#   endif ()

   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${this_system_libraries} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



