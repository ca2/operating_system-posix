
if(${XFCE_DESKTOP})
   set(GNOME_RELEASE_MAJOR "3")
   set(HAS_GTK3 TRUE)
   message(STATUS "HAS_GTK3 is ${HAS_GTK3}")
   add_compile_definitions(HAS_GTK3)
   add_compile_definitions(__XFCE)
elseif(${LINUX_MINT})
   set(GNOME_RELEASE_MAJOR "3")
   set(HAS_GTK3 TRUE)
   message(STATUS "HAS_GTK3 is ${HAS_GTK3}")
   add_compile_definitions(HAS_GTK3)
   add_compile_definitions(__LINUX_MINT)
elseif(${GTK_BASED_DESKTOP})
   execute_process(COMMAND gnome-shell --version OUTPUT_VARIABLE GNOME_SHELL_VERSION_RAW OUTPUT_STRIP_TRAILING_WHITESPACE)
   message(STATUS "GNOME_SHELL_VERSION_RAW is ${GNOME_SHELL_VERSION_RAW}")
   string(TOLOWER ${GNOME_SHELL_VERSION_RAW} GNOME_RELEASE)
   #message(STATUS "GNOME_RELEASE now is ${GNOME_RELEASE}")
   string(REPLACE "gnome" "" GNOME_RELEASE ${GNOME_RELEASE})
   string(REPLACE "shell" "" GNOME_RELEASE ${GNOME_RELEASE})
   string(STRIP ${GNOME_RELEASE} GNOME_RELEASE)
   message(STATUS "GNOME_RELEASE is ${GNOME_RELEASE}")
   string(FIND ${GNOME_RELEASE} "." GNOME_RELEASE_FIRST_DOT)
   string(SUBSTRING ${GNOME_RELEASE} 0 ${GNOME_RELEASE_FIRST_DOT} GNOME_RELEASE_MAJOR)
   message(STATUS "GNOME_RELEASE_MAJOR is ${GNOME_RELEASE_MAJOR}")
   if(${GNOME_RELEASE_MAJOR} GREATER_EQUAL 40)
      set(HAS_GTK4 TRUE)
      message(STATUS "HAS_GTK4 is ${HAS_GTK4}")
      add_compile_definitions(HAS_GTK4)
      set(GNOME_RELEASE_MAJOR "4")
      set(APPINDICATOR_PKG_MODULE "")
   elseif(${GNOME_RELEASE_MAJOR} GREATER_EQUAL 3)
      set(HAS_GTK3 TRUE)
      message(STATUS "HAS_GTK3 is ${HAS_GTK3}")
      add_compile_definitions(HAS_GTK3)
      set(GNOME_RELEASE_MAJOR "3")
   endif()

endif()
