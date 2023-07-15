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
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
elseif (LINUX)


   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   #target_link_options(music_midi_alsa PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   target_link_libraries(${PROJECT_NAME} PRIVATE asound)
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


target_compile_definitions(${PROJECT_NAME} PRIVATE _MUSIC_MIDI_ALSA_LIBRARY)



