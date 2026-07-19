
if(NOT ${GTK_BASED_DESKTOP})
message(ERROR error)
endif()

if(${LABWC_DESKTOP})

set(GNOME_RELEASE_MAJOR "4")
set(GTK_RELEASE_MAJOR 4)
add_compile_definitions(__LABWC)

elseif(${XFCE_DESKTOP})

set(GNOME_RELEASE_MAJOR "3")
set(GTK_RELEASE_MAJOR 3)
add_compile_definitions(__XFCE)


#if(${LXDE_DESKTOP})

   #set(GNOME_RELEASE_MAJOR "3")
   #set(GTK_RELEASE_MAJOR 3)
   #add_compile_definitions(__XFCE)

#elseif(${XFCE_DESKTOP})

   #set(GNOME_RELEASE_MAJOR "3")
   #set(GTK_RELEASE_MAJOR 3)
   #add_compile_definitions(__XFCE)

#elseif(${LINUX_MINT})

   #set(GNOME_RELEASE_MAJOR "3")
   #set(GTK_RELEASE_MAJOR 3)
   #add_compile_definitions(__LINUX_MINT)

#elseif(${GTK_BASED_DESKTOP})

else()

   #find_package(PkgConfig REQUIRED)
   # Try to find GTK 4 first
   pkg_check_modules(GTK4 QUIET gtk4)
   if(GTK4_FOUND)
      message(STATUS "GTK 4 found: ${GTK4_VERSION}")
      set(GTK_RELEASE ${GTK4_VERSION})
#     set(GTK_INCLUDE_DIRS ${GTK4_INCLUDE_DIRS})
#     set(GTK_LIBRARIES ${GTK4_LIBRARIES})
#     set(GTK_CFLAGS_OTHER ${GTK4_CFLAGS_OTHER})
#     set(GTK_VERSION 4)
   else()
      # Fallback to GTK 3
      pkg_check_modules(GTK3 QUIET gtk+-3.0)
      if(GTK3_FOUND)
         message(STATUS "GTK 3 found: ${GTK3_VERSION}")
         set(GTK_RELEASE ${GTK3_VERSION})
#        set(GTK_INCLUDE_DIRS ${GTK3_INCLUDE_DIRS})
#        set(GTK_LIBRARIES ${GTK3_LIBRARIES})
#        set(GTK_CFLAGS_OTHER ${GTK3_CFLAGS_OTHER})
#        set(GTK_VERSION 3)
      else()
         message(FATAL_ERROR "Neither GTK 4 nor GTK 3 could be found. Please install GTK development packages.")
      endif()
   endif()


   find_package(PkgConfig REQUIRED)

   message(STATUS "PKG_CONFIG_EXECUTABLE=${PKG_CONFIG_EXECUTABLE}")
   message(STATUS "PKG_CONFIG_PATH=$ENV{PKG_CONFIG_PATH}")
   message(STATUS "PKG_CONFIG_LIBDIR=$ENV{PKG_CONFIG_LIBDIR}")
   message(STATUS "PKG_CONFIG_SYSROOT_DIR=$ENV{PKG_CONFIG_SYSROOT_DIR}")

   execute_process(
      COMMAND "${PKG_CONFIG_EXECUTABLE}" --modversion gtk4
      RESULT_VARIABLE GTK4_PKG_RESULT
      OUTPUT_VARIABLE GTK4_PKG_OUTPUT
      ERROR_VARIABLE GTK4_PKG_ERROR
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
   )

   message(STATUS "gtk4 result=${GTK4_PKG_RESULT}")
   message(STATUS "gtk4 version=${GTK4_PKG_OUTPUT}")
   message(STATUS "gtk4 error=${GTK4_PKG_ERROR}")

   execute_process(
      COMMAND "${PKG_CONFIG_EXECUTABLE}" --modversion gtk+-3.0
      RESULT_VARIABLE GTK3_PKG_RESULT
      OUTPUT_VARIABLE GTK3_PKG_OUTPUT
      ERROR_VARIABLE GTK3_PKG_ERROR
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
   )

   message(STATUS "gtk+-3.0 result=${GTK3_PKG_RESULT}")
   message(STATUS "gtk+-3.0 version=${GTK3_PKG_OUTPUT}")
   message(STATUS "gtk+-3.0 error=${GTK3_PKG_ERROR}")

   pkg_check_modules(GTK4 QUIET gtk4)

   message(STATUS "GTK4_FOUND=${GTK4_FOUND}")
   message(STATUS "GTK4_VERSION=${GTK4_VERSION}")
   message(STATUS "GTK4_PKGCONFIG_EXECUTABLE=${PKG_CONFIG_EXECUTABLE}")

   if(GTK4_FOUND)

      message(STATUS "GTK 4 found: ${GTK4_VERSION}")
      set(GTK_RELEASE "${GTK4_VERSION}")
      set(GTK_VERSION 4)

   else()

      pkg_check_modules(GTK3 QUIET gtk+-3.0)

      message(STATUS "GTK3_FOUND=${GTK3_FOUND}")
      message(STATUS "GTK3_VERSION=${GTK3_VERSION}")

      if(GTK3_FOUND)

         message(STATUS "GTK 3 found: ${GTK3_VERSION}")
         set(GTK_RELEASE "${GTK3_VERSION}")
         set(GTK_VERSION 3)

      else()

         message(FATAL_ERROR
            "Neither GTK 4 nor GTK 3 could be found.\n"
            "gtk4 pkg-config error: ${GTK4_PKG_ERROR}\n"
            "gtk3 pkg-config error: ${GTK3_PKG_ERROR}")

      endif()

   endif()
   # Print the detected GTK version
   message(STATUS "GTK_RELEASE is ${GTK_RELEASE}")

   #find_program(GNOME_SHELL "gnome-shell")
   #if(GNOME_SHELL)
   #  message(STATUS "Found gnome-shell : ${GNOME_SHELL}")
   #  execute_process(COMMAND ${GNOME_SHELL} --version OUTPUT_VARIABLE GNOME_SHELL_VERSION_RAW OUTPUT_STRIP_TRAILING_WHITESPACE)
   #else()
   #  message(STATUS "gnome-shell not found")
   #endif()
   #message(STATUS "GNOME_SHELL_VERSION_RAW is ${GNOME_SHELL_VERSION_RAW}")
   #string(TOLOWER ${GNOME_SHELL_VERSION_RAW} GNOME_RELEASE)
   #message(STATUS "GNOME_RELEASE now is ${GNOME_RELEASE}")
   string(FIND ${GTK_RELEASE} "." GTK_RELEASE_FIRST_DOT)
   string(SUBSTRING ${GTK_RELEASE} 0 ${GTK_RELEASE_FIRST_DOT} GTK_RELEASE_MAJOR)
   message(STATUS "GTK_RELEASE_MAJOR is ${GTK_RELEASE_MAJOR}")

   math(EXPR GTK_RELEASE_MAJOR ${GTK_RELEASE_MAJOR})

endif()


if(${GTK_RELEASE_MAJOR} GREATER_EQUAL 4)

   set(HAS_GTK4 TRUE)
   set(GTK_RELEASE_MAJOR "4")
   #set(APPINDICATOR_PKG_MODULE "")
   
   add_compile_definitions(HAS_GTK4)

   message(STATUS "HAS_GTK4 is TRUE")

elseif(${GTK_RELEASE_MAJOR} GREATER_EQUAL 3)

   set(HAS_GTK3 TRUE)
   set(GTK_RELEASE_MAJOR "3")
   
   add_compile_definitions(HAS_GTK3)

   message(STATUS "HAS_GTK3 is TRUE")

endif()



