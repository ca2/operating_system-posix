//
// Created by camilo on 2024-10-03 01:14 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_gtk4.h"


#define GDK_SURFACE_EDGE_NONE ((GdkSurfaceEdge)-1)


GdkSurfaceEdge as_gdk_surface_edge(::experience::enum_frame eframeSizing)
{

   switch (eframeSizing)
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



guint as_guint_button(::user::e_button_state ebuttonstate)
{

   guint button = 1;

   if (ebuttonstate & user::e_button_state_left)
   {

      button = 1;

   }
   else if (ebuttonstate & user::e_button_state_right)
   {

      button = 3;

   }
   else if (ebuttonstate & user::e_button_state_middle)
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





