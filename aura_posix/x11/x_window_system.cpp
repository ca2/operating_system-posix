//
// Created by camilo on 05/03/2021. 22:54 BRT ThomasBS_!!
//
#include "framework.h"
#include "x_window_system.h"
#include <X11/cursorfont.h>

namespace x_window
{


   const char * g_pszAtomName[] = {
      "_NET_WM_STATE",
      "_NET_WM_STATE_ABOVE",
      "_NET_WM_STATE_BELOW",
      "_NET_WM_STATE_HIDDEN",
      "_NET_WM_STATE_MAXIMIZED_HORZ",
      "_NET_WM_STATE_MAXIMIZED_VERT",
      "_NET_WM_STATE_FULLSCREEN",
      "_NET_WM_STATE_SKIP_TASKBAR",
      "WM_NAME",
      "WM_STATE",
      "_NET_ACTIVE_WINDOW",
      "_NET_CLIENT_LIST_STACKING",
      "_NET_CLIENT_LIST",
      "_NET_WM_WINDOW_TYPE",
      "_NET_WM_WINDOW_TYPE_NORMAL",
      "_NET_WM_WINDOW_TYPE_SPLASH",
      "_NET_WM_CM_S0",

   };


   const char * atom_name(enum_atom eatom)
   {

      int iAtom = (int) eatom;

      if (iAtom < 0 || iAtom >= e_atom_count)
      {

         return nullptr;

      }

      return g_pszAtomName[iAtom];

   }


   int atom_count()
   {

      return e_atom_count;

   }


   int get_default_system_cursor_glyph(enum_cursor ecursor)
   {

      int iCursor;

      if(ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if(ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if(ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if(ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if(ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if(ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if(ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if(ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if(ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }
      else
      {

         iCursor = -1;

      }

      return iCursor;

   }



} // namespace x_window




