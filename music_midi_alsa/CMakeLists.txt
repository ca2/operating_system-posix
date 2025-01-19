cmake_minimum_required(VERSION 3.16)
project(music_midi_alsa CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   _factory.cpp
   midi.cpp
   midi.h
   out.cpp
   out.h
   translation.cpp
   translation.h
   framework.cpp
   framework.h
   message_out.cpp
   message_out.h
   translation.cpp
   translation.h
   )


list(APPEND library_references
   acme
   apex
   aqua
   aura
   veriwell_multimedia
   )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
elseif (LINUX)


   pkg_check_modules(PKGCONFIG alsa)


   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



