cmake_minimum_required(VERSION 3.16)
project(aura_posix CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   _factory.cpp
   framework.cpp
   framework.h
   node.cpp
   node.h
   shell.cpp
   shell.h
   user_notify_icon_bridge.h
   xinput.cpp
   xinput.h
)


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
)

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)



add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(aura_posix PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(aura_posix PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(aura_posix PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(aura_posix PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)





   if(${WITH_XCB} OR ${WITH_X11})
      list(APPEND extra_pkg_modules
         #libstartupxxx-notification-1.0
         xkbcommon
         )

   if(WITH_XCB)


      list(APPEND extra_pkg_modules
                  x11 x11-xcb
         )


   else()


      list(APPEND extra_pkg_modules
                  x11
         )


   endif()

   endif()



   #if (${USE_PKGCONFIG})
   if(NOT "${extra_pkg_modules}" STREQUAL "")
   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG ${extra_pkg_modules})
   endif ()
   #endif ()


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_link_options(aura_posix PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${library_references} ${global_library_references})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${static_library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



