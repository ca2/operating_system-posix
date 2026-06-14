//
// Created by camilo on 2024-10-03 01:14 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_gtk4.h"


#define GDK_SURFACE_EDGE_NONE ((GdkSurfaceEdge)-1)
#include <gtk/gtk.h>
#include <gio/gio.h>

bool gtk4_is_session_dbus_available()
{
   GError *error = NULL;
   GDBusConnection *connection =
       g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);

   if (connection != NULL)
   {
      g_object_unref(connection);
      return true;
   }

   if (error != NULL)
   {
      g_printerr("Failed to connect to session bus: %s\n", error->message);
      g_error_free(error);
   }

   return false;
}

// int main(int argc, char *argv[])
// {
//    gtk_init();
//
//    if (is_session_dbus_available())
//       g_print("Session D-Bus is available\n");
//    else
//       g_print("Session D-Bus is NOT available\n");
//
//    return 0;
// }

GdkSurfaceEdge as_gdk_surface_edge(const ::experience::e_frame & eframeSizing)
{

   switch (eframeSizing.m_cflag)
   {
      case ::experience::e_frame_sizing_bottom:
         return GDK_SURFACE_EDGE_SOUTH;
      case ::experience::e_frame_sizing_bottom_left:
         return GDK_SURFACE_EDGE_SOUTH_WEST;
      case ::experience::e_frame_sizing_bottom_right:
         return GDK_SURFACE_EDGE_SOUTH_EAST;
      case ::experience::e_frame_sizing_left:
         return GDK_SURFACE_EDGE_WEST;
      case ::experience::e_frame_sizing_right:
         return GDK_SURFACE_EDGE_EAST;
      case ::experience::e_frame_sizing_top_left:
         return GDK_SURFACE_EDGE_NORTH_WEST;
      case ::experience::e_frame_sizing_top_right:
         return GDK_SURFACE_EDGE_NORTH_EAST;
      case ::experience::e_frame_sizing_top:
         return GDK_SURFACE_EDGE_NORTH;
      default:
         return GDK_SURFACE_EDGE_NONE;
   }

}



guint as_guint_button(const ::user::e_key_state & ekeystate)
{

   guint button = 1;

   if (ekeystate & user::e_key_state_left_button)
   {

      button = 1;

   }
   else if (ekeystate & user::e_key_state_right_button)
   {

      button = 3;

   }
   else if (ekeystate & user::e_key_state_middle_button)
   {

      button = 2;

   }

   return button;

}


//bool is_control_character(ansi_character ansich)
//{
//
//   return ansich >= 0 && ansich <= 31;
//
//}
//
//
//bool is_control_character(const ::scoped_string & scopedstr)
//{
//
//   return scopedstr.length_in_bytes() == 1 && ::is_control_character(scopedstr.begin()[0]);
//
//}





