
message("_desktop_ambient_1.cmake begin ------------")


if(${DESKTOP_AMBIENT})



   message("DESKTOP_AMBIENT is set")
   

   if(DEFINED SYSROOT_XDG_CURRENT_DESKTOP)
      set(CURRENT_DESKTOP_ENVIRONMENT ${SYSROOT_XDG_CURRENT_DESKTOP})
   else()
      set(CURRENT_DESKTOP_ENVIRONMENT $ENV{XDG_CURRENT_DESKTOP})
   endif()

   message(STATUS "XDG_CURRENT_DESKTOP is ${CURRENT_DESKTOP_ENVIRONMENT}")

   string(TOLOWER "${CURRENT_DESKTOP_ENVIRONMENT}" LOWERCASE_CURRENT_DESKTOP_ENVIRONMENT)

   if ("${LOWERCASE_CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "lxqt"
   OR LOWERCASE_CURRENT_DESKTOP_ENVIRONMENT MATCHES "^(lxqt:)|(:lxqt$)|(:lxqt:)")

      set(LXQT_DESKTOP TRUE)
      message(STATUS "System is LXQt")
      set(DESKTOP_ENVIRONMENT_NAME "lxqt")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "KDE")

      set(KDE_DESKTOP TRUE)
      message(STATUS "System is KDE")
      set(DESKTOP_ENVIRONMENT_NAME "kde")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "ubuntu:GNOME")

      set(GNOME_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      message(STATUS "System is GNOME")
      set(DESKTOP_ENVIRONMENT_NAME "gnome")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "GNOME")

      set(GNOME_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      message(STATUS "System is GNOME")
      set(DESKTOP_ENVIRONMENT_NAME "gnome")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "LXDE")

      set(LXDE_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      message(STATUS "System is LXDE")
      set(DESKTOP_ENVIRONMENT_NAME "lxde")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "XFCE")

      set(XFCE_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is XFCE")
      set(DESKTOP_ENVIRONMENT_NAME "xfce")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "MATE")

      set(XFCE_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is MATE")
      set(DESKTOP_ENVIRONMENT_NAME "mate")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" STREQUAL "X-Cinnamon")

      set(XCINNAMON_DESKTOP TRUE)
      set(GTK_BASED_DESKTOP TRUE)
      set(HAS_WAYLAND FALSE)
      message(STATUS "System is X-Cinnamon")
      set(DESKTOP_ENVIRONMENT_NAME "xcinnamon")

   elseif ("${CURRENT_DESKTOP_ENVIRONMENT}" MATCHES "labwc"
   AND "${CURRENT_DESKTOP_ENVIRONMENT}" MATCHES "wlroots")

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


   if(${LXQT_DESKTOP})

      include(${WORKSPACE_FOLDER}/operating_system/operating_system-posix/_lxq_desktop.cmake)

   elseif(${KDE_DESKTOP})

      include(${WORKSPACE_FOLDER}/operating_system/operating_system-posix/_kde_desktop.cmake)

   elseif(${GTK_BASED_DESKTOP})

      include(${WORKSPACE_FOLDER}/operating_system/operating_system-posix/_gtk_desktop.cmake)

   endif()


   message(STATUS "DESKTOP_ENVIRONMENT_NAME is ${DESKTOP_ENVIRONMENT_NAME}")

   # DESKTOP_AMBIENT are dependant just on linux kernel version and glib version?

endif()



message("_desktop_ambient_1.cmake end ------------")




