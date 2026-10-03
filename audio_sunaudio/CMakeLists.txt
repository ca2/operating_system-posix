cmake_minimum_required(VERSION 3.16)
project(audio_sunaudio CXX)

if(__SUNOS__)
   find_path(SUNOS_AUDIO_INCLUDE_DIR NAMES sys/audioio.h)
   if(NOT SUNOS_AUDIO_INCLUDE_DIR)
      message(FATAL_ERROR
         "SunOS audio development headers are missing (sys/audioio.h). "
         "Install them with: sudo pkg install system/header/header-audio")
   endif()
endif()

list(APPEND library_source
   _.h
   #_library.h
   _factory.cpp
   audio_mmsystem_wave_in.h
   #cmus_sndio.cpp
   platform.cpp
   platform.h
#   snd_pcm.cpp
#   snd_pcm.h
sunaudio.cpp
sunaudio.h
   timo_mixer.h
   #timo_output_plugin.cpp
   #timo_output_plugin.h
   #timo_sample_format.h
   translation.cpp
   translation.h
#   wave_in.cpp
#   wave_in.h
   wave_out.cpp
   wave_out.h
   )


if(__SUNOS__)
   list(APPEND library_source sunaudio_streams.cpp sunaudio_streams.h)
   set_source_files_properties(sunaudio_streams.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
else()
   list(APPEND library_source audiodev.cpp audiodev.h drvctl.cpp drvctl.h)
endif()

list(APPEND library_references
   acme
   apex
   aqua
   audio
   )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if(__SUNOS__)
   target_include_directories(${PROJECT_NAME} PUBLIC ${SUNOS_AUDIO_INCLUDE_DIR})
   target_include_directories(static_${PROJECT_NAME} PUBLIC ${SUNOS_AUDIO_INCLUDE_DIR})
endif()

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if(${WIN32})


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${__ANDROID__} OR ${__SUNOS__})


# Device discovery uses NetBSD proplib, not sndio.
   if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
      list(APPEND library_references prop)
   endif()


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   set(static_library_references acme apex aqua audio)
   list(TRANSFORM static_library_references PREPEND static_)
   if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
      list(APPEND static_library_references prop)
   endif()
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${global_library_references})

   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



