#include "framework.h"
#include <X11/XKBlib.h>
#define XK_MISCELLANY
#define XK_XKB_KEYS
#define XK_LATIN1
#define XK_LATIN2
#define XK_LATIN3
#define XK_LATIN4
#define XK_CYRILLIC
#define XK_GREEK
#define XK_ARMENIAN
#include <X11/keysymdef.h>


namespace windowing_xcb
{

   
   CLASS_DECL_WINDOWING_XCB ::user::enum_key keysym_to_userkey(const lparam & lparam)
   {

      KeySym keysym = (KeySym) (iptr)lparam.m_lparam;

      switch(keysym)
      {
         case XK_BackSpace:
            return ::user::e_key_back;
         case XK_Shift_L:
            return ::user::e_key_left_shift;
         case XK_Shift_R:
            return ::user::e_key_right_shift;
         case XK_Control_L:
            return ::user::e_key_left_control;
         case XK_Control_R:
            return ::user::e_key_right_control;
         case XK_Alt_L:
            return ::user::e_key_left_alt;
         case XK_Alt_R:
            return ::user::e_key_right_alt;
         case XK_Delete:
            return ::user::e_key_delete;
         case XK_Return:
            return ::user::e_key_return;
         case XK_Tab:
            return ::user::e_key_tab;
         case XK_Left:
            return ::user::e_key_left;
         case XK_Right:
            return ::user::e_key_right;
         case XK_Up:
            return ::user::e_key_up;
         case XK_Down:
            return ::user::e_key_down;
         case XK_Page_Up:
            return ::user::e_key_prior;
         case XK_Page_Down:
            return ::user::e_key_next;
         case XK_Home:
            return ::user::e_key_home;
         case XK_End:
            return ::user::e_key_end;
      }

      if(keysym >= 'a' && keysym <= 'z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'a');

      }
      else if(keysym >= 'A' && keysym <= 'Z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'A');

      }

      return ::user::e_key_none;

   }


} // namespace windowing_xcb



