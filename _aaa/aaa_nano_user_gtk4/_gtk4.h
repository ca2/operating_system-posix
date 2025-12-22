//
// Created by camilo on 01/01/2021. 6:52 BRT <3Tbs, Mummi and bilbo!!
//
// From _.h by camilo on 2022-09-24 23:21 <3ThomasBorregaardSorensen!!
// From windowing_wayland by camilo on 2024-09-14 14:14:14 <3ThomasBorregaardSorensen!!
#pragma once


#include <gtk/gtk.h>


# ifdef GDK_WINDOWING_X11
#  include <gdk/x11/gdkx.h>
# endif
# ifdef GDK_WINDOWING_WAYLAND
#  include <gdk/wayland/gdkwayland.h>
#endif


CLASS_DECL_NANO_USER_GTK4 guint as_guint_button(::user::e_button_state ebuttonstate);

CLASS_DECL_NANO_USER_GTK4 GdkSurfaceEdge as_gdk_surface_edge(::experience::enum_frame eframeSizing);



