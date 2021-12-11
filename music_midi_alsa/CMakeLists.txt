cmake_minimum_required(VERSION 3.17)
project(music_midi_alsa CXX)


list(APPEND library_source
   _.cpp
   _.h
   _music_midi_alsa.h
   midi.cpp
   midi.h
   out.cpp
   out.h
   factory_exchange.cpp
   factory_exchange.h
   translation.cpp
   translation.h
   factory_exchange.cpp
   factory_exchange.h
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


add_library(music_midi_alsa SHARED ${library_source} )

target_precompile_headers(music_midi_alsa PRIVATE framework.h)

set_target_properties(music_midi_alsa PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(music_midi_alsa PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(music_midi_alsa PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(music_midi_alsa PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(music_midi_alsa PRIVATE ${library_references})
elseif (LINUX)
   target_compile_options(music_midi_alsa PRIVATE -fpermissive)
   #target_link_options(music_midi_alsa PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(music_midi_alsa PRIVATE ${library_references})
   target_link_libraries(music_midi_alsa PRIVATE asound)
   target_link_options(music_midi_alsa PRIVATE -Wl,-z,defs)
endif ()





target_include_directories(music_midi_alsa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(music_midi_alsa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(music_midi_alsa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(music_midi_alsa PRIVATE _MUSIC_MIDI_ALSA_LIBRARY)



