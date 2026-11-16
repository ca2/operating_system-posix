
message("_desktop_ambient_1.cmake begin ------------")


if(DESKTOP_AMBIENT)



   message(STATUS "DESKTOP_AMBIENT is set")

   # Clear prior selection in case this file is included more than once.
   set(LXQT_DESKTOP FALSE)
   set(KDE_DESKTOP FALSE)
   set(GNOME_DESKTOP FALSE)
   set(LXDE_DESKTOP FALSE)
   set(XFCE_DESKTOP FALSE)
   set(MATE_DESKTOP FALSE)
   set(XCINNAMON_DESKTOP FALSE)
   set(LABWC_DESKTOP FALSE)
   set(GTK_BASED_DESKTOP FALSE)
   set(DESKTOP_ENVIRONMENT_NAME "")
   

   # Explicit overrides work for IDE/remote builds without a desktop environment.
   # The CMake variable (-D__AMBIENT=xfce) takes priority.
   if(DEFINED __AMBIENT AND NOT "${__AMBIENT}" STREQUAL "")
      set(CURRENT_DESKTOP_ENVIRONMENT "${__AMBIENT}")
   elseif(DEFINED ENV{__AMBIENT} AND NOT "$ENV{__AMBIENT}" STREQUAL "")
      set(CURRENT_DESKTOP_ENVIRONMENT "$ENV{__AMBIENT}")
   elseif(DEFINED SYSROOT_XDG_CURRENT_DESKTOP)
      set(CURRENT_DESKTOP_ENVIRONMENT "${SYSROOT_XDG_CURRENT_DESKTOP}")
   else()
      set(CURRENT_DESKTOP_ENVIRONMENT $ENV{XDG_CURRENT_DESKTOP})
   endif()

   message(STATUS "Desktop probe: system=${CMAKE_SYSTEM_NAME}; cross=${CMAKE_CROSSCOMPILING}")
   message(STATUS "Desktop inputs: SYSROOT_XDG_CURRENT_DESKTOP='${SYSROOT_XDG_CURRENT_DESKTOP}'; XDG_CURRENT_DESKTOP='$ENV{XDG_CURRENT_DESKTOP}'; __AMBIENT='${__AMBIENT}'; ENV{__AMBIENT}='$ENV{__AMBIENT}'")
   string(STRIP "${CURRENT_DESKTOP_ENVIRONMENT}" CURRENT_DESKTOP_ENVIRONMENT)
   string(TOLOWER "${CURRENT_DESKTOP_ENVIRONMENT}" _ca2_desktop_value)
   if(_ca2_desktop_value STREQUAL "unknown" OR _ca2_desktop_value STREQUAL "none")
      message(STATUS "Desktop probe: '${CURRENT_DESKTOP_ENVIRONMENT}' does not identify a desktop")
      set(CURRENT_DESKTOP_ENVIRONMENT "")
   endif()

   # Match the SunOS runtime fallback when no desktop is reported.
   if(CMAKE_SYSTEM_NAME STREQUAL "SunOS" AND NOT CURRENT_DESKTOP_ENVIRONMENT)
      set(CURRENT_DESKTOP_ENVIRONMENT "gnome")
      message(STATUS "No desktop reported; using SunOS GNOME fallback")
   endif()

   message(STATUS "Current desktop environment is ${CURRENT_DESKTOP_ENVIRONMENT}")

   string(TOLOWER "${CURRENT_DESKTOP_ENVIRONMENT}" LOWERCASE_CURRENT_DESKTOP_ENVIRONMENT)

   # Match XDG colon-delimited desktops (e.g. ubuntu:GNOME) without
   # treating arbitrary substrings as desktop names.
   string(REPLACE ":" ";" CA2_DESKTOP_IDENTIFIERS "${LOWERCASE_CURRENT_DESKTOP_ENVIRONMENT}")

   if("lxqt" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(LXQT_DESKTOP TRUE)
      message(STATUS "System is LXQt")
      set(DESKTOP_ENVIRONMENT_NAME "lxqt")

   elseif("kde" IN_LIST CA2_DESKTOP_IDENTIFIERS OR "plasma" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(KDE_DESKTOP TRUE)
      message(STATUS "System is KDE")
      set(DESKTOP_ENVIRONMENT_NAME "kde")

   elseif("gnome" IN_LIST CA2_DESKTOP_IDENTIFIERS OR "gnome-classic" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(GNOME_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      message(STATUS "System is GNOME")
      set(DESKTOP_ENVIRONMENT_NAME "gnome")

   elseif("lxde" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(LXDE_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      message(STATUS "System is LXDE")
      set(DESKTOP_ENVIRONMENT_NAME "lxde")

   elseif("xfce" IN_LIST CA2_DESKTOP_IDENTIFIERS OR "xfce4" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(XFCE_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is XFCE")
      set(DESKTOP_ENVIRONMENT_NAME "xfce")

   elseif("mate" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(MATE_DESKTOP TRUE)
      set(XFCE_DESKTOP TRUE) # Existing GTK3 ambient selection for MATE.
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is MATE")
      set(DESKTOP_ENVIRONMENT_NAME "mate")

   elseif("x-cinnamon" IN_LIST CA2_DESKTOP_IDENTIFIERS OR "cinnamon" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(XCINNAMON_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is X-Cinnamon")
      set(DESKTOP_ENVIRONMENT_NAME "xcinnamon")

   elseif("labwc" IN_LIST CA2_DESKTOP_IDENTIFIERS)

      set(LABWC_DESKTOP TRUE)
      # it is not gtk based, but maybe better to rely on gtk4 for
      # developing for it, instead of creating another stack over
      # the labwc toolkit.
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND TRUE)
      message(STATUS "System is labwc:wlroots. Gonna use gtk4 UI toolkit")
      set(DESKTOP_ENVIRONMENT_NAME "gnome")
      #set(BUILD_GPU_BASED_APPLICATIONS FALSE)

   endif ()


   if(LXQT_DESKTOP)

      include("${CMAKE_CURRENT_LIST_DIR}/_lxq_desktop.cmake")

   elseif(KDE_DESKTOP)

      include("${CMAKE_CURRENT_LIST_DIR}/_kde_desktop.cmake")

   elseif(GTK_BASED_DESKTOP)

      find_package(PkgConfig REQUIRED)
      include("${CMAKE_CURRENT_LIST_DIR}/_gtk_desktop.cmake")

   endif()


   # Report the selected desktop and the backend version determined above.
   # GTK's release is a toolkit version, not the desktop's own release.
   if(LXQT_DESKTOP)
      message(STATUS "Desktop ambient selection: desktop=${DESKTOP_ENVIRONMENT_NAME}; LXQt version=${LXQ_RELEASE}; ambient major=${LXQ_RELEASE_MAJOR}")
   elseif(KDE_DESKTOP)
      message(STATUS "Desktop ambient selection: desktop=${DESKTOP_ENVIRONMENT_NAME}; Plasma version=${PLASMA_RELEASE}; ambient major=${PLASMA_RELEASE_MAJOR}")
   elseif(GTK_BASED_DESKTOP)
      set(_ca2_desktop_label "${DESKTOP_ENVIRONMENT_NAME}")
      if(LABWC_DESKTOP)
         set(_ca2_desktop_label "labwc")
      endif()
      set(_ca2_gtk_release "${GTK_RELEASE}")
      if("${_ca2_gtk_release}" STREQUAL "")
         set(_ca2_gtk_release "not detected")
      endif()
      message(STATUS "Desktop ambient selection: desktop=${_ca2_desktop_label}; GTK version=${_ca2_gtk_release}; ambient major=${GTK_RELEASE_MAJOR}")
   else()
      message(STATUS "Desktop ambient selection: no supported desktop selected (input='${CURRENT_DESKTOP_ENVIRONMENT}')")
   endif()

   # DESKTOP_AMBIENT are dependant just on linux kernel version and glib version?

else()
   message(STATUS "Desktop ambient selection: disabled (DESKTOP_AMBIENT is off)")
endif()



message("_desktop_ambient_1.cmake end ------------")




