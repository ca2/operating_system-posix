//
// Created by camilo on 2024-12-20 03:22 <3ThomasBorregaardSorensen
//
#include "framework.h"
#include "acme/constant/user_key.h"
#include <gdk/gdkkeysyms.h>


CLASS_DECL_ACME_WINDOWING_G ::user::e_key gtk_key_as_user_ekey(unsigned long long uGtkKey)
{

   switch(uGtkKey)
   {

      case GDK_KEY_Delete:
         return ::user::e_key_delete;
      case GDK_KEY_BackSpace:
         return ::user::e_key_back;
      case GDK_KEY_Left:
         return ::user::e_key_left;
      case GDK_KEY_Right:
         return ::user::e_key_right;
      case GDK_KEY_Up:
         return ::user::e_key_up;
      case GDK_KEY_Down:
         return ::user::e_key_down;
      case GDK_KEY_Return:
         return ::user::e_key_return;
      case GDK_KEY_Tab:
         return ::user::e_key_tab;
      case GDK_KEY_Shift_L:
         return ::user::e_key_left_shift;
      case GDK_KEY_Shift_R:
         return ::user::e_key_right_shift;
      case GDK_KEY_Control_L:
         return ::user::e_key_left_control;
      case GDK_KEY_Control_R:
         return ::user::e_key_right_control;
      case GDK_KEY_Alt_L:
         return ::user::e_key_left_alt;
      case GDK_KEY_Alt_R:
         return ::user::e_key_right_alt;
      case GDK_KEY_Super_L:
         return ::user::e_key_left_command;
      case GDK_KEY_Super_R:
         return ::user::e_key_right_command;
      case GDK_KEY_Page_Down:
         return ::user::e_key_page_down;
      case GDK_KEY_Page_Up:
         return ::user::e_key_page_up;
   }
   return ::user::e_key_none;


}

