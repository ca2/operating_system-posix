cmake_minimum_required(VERSION 3.16)
project(audio_alsa CXX)


list(APPEND library_source
   _.h
   #_library.h
   _factory.cpp
   audio_mmsystem_wave_in.h
   framework.cpp
   framework.h
   snd_pcm.cpp
   snd_pcm.h
   translation.cpp
   translation.h
   wave_in.cpp
   wave_in.h
   wave_out.cpp
   wave_out.h
   )


list(APPEND library_references
   acme
   apex
   aqua
   audio
   )


add_library(audio_alsa SHARED ${library_source} )


target_precompile_headers(audio_alsa PRIVATE framework.h)


set_target_properties(audio_alsa PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(audio_alsa PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(audio_alsa PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(audio_alsa PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(audio_alsa PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG alsa)
   endif()
   target_compile_options(audio_alsa PRIVATE -fpermissive)
   target_compile_options(audio_alsa PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(audio_alsa PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(audio_alsa PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(audio_alsa PRIVATE ${library_references})
   target_link_options(audio_alsa PRIVATE -Wl,-z,defs)


endif()


add_dependencies(audio_alsa audio)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(audio_alsa PRIVATE _AUDIO_ALSA_LIBRARY)



