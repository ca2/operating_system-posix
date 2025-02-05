
list(APPEND static_app_common_dependencies
   static_operating_ambient_gtk4
   static_node_gnome
   static_node_gtk
   static_node_linux)

set(default_common_windowing common_gtk)

if(${HAS_GTK4})

   message(STATUS "Setting up GTK4 dependencies.")

   set(default_acme_windowing acme_windowing_gtk4)

   set(default_innate_ui innate_ui_gtk4)

   set(default_windowing_common windowing_posix)

   set(default_windowing windowing_gtk4)

   set(default_operating_ambient operating_ambient_gtk4)

   set(default_node node_gtk4)

elseif (${HAS_GTK3})

   message(STATUS "Setting up GTK3 dependencies.")

   set(default_acme_windowing acme_windowing_gtk3)

   set(default_innate_ui innate_ui_gtk3)

   set(default_windowing_common windowing_posix)

   set(default_windowing windowing_gtk3)

   set(default_operating_ambient operating_ambient_gtk3)

   set(default_node node_gtk3)


else()

   message(STATUS "Adding GNOME/X11 dependency.")

   list(APPEND app_common_dependencies nano_graphics_cairo operating_ambient_gtk_based)

   list(APPEND static_app_common_dependencies
      static_desktop_environment_gnome
      static_node_gnome
      static_node_gtk
      static_node_linux
      static_windowing_x11)

   set(default_windowing "windowing_x11")

   set(default_operating_ambient operating_ambient_gtk_based)

   add_compile_definitions(DESKTOP_ENVIRONMENT_GTK_BASED)

endif()

add_compile_definitions(DESKTOP_ENVIRONMENT_GNOME)
