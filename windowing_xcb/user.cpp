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

namespace user
{

   
   CLASS_DECL_WINDOWING_XCB ::user::enum_key keysym_to_userkey(const lparam & lparam)
   {

      KeySym keysym = (KeySym) (iptr)lparam.m_lparam;

      switch(keysym)
      {
         case XK_BackSpace:
            return e_key_back;
         case XK_Shift_L:
            return e_key_lshift;
         case XK_Shift_R:
            return e_key_rshift;
         case XK_Control_L:
            return e_key_lcontrol;
         case XK_Control_R:
            return e_key_rcontrol;
         case XK_Alt_L:
            return e_key_lalt;
         case XK_Alt_R:
            return e_key_ralt;
         case XK_Delete:
            return e_key_delete;
         case XK_Return:
            return e_key_return;
         case XK_Tab:
            return e_key_tab;
         case XK_Left:
            return e_key_left;
         case XK_Right:
            return e_key_right;
         case XK_Up:
            return e_key_up;
         case XK_Down:
            return e_key_down;
         case XK_Page_Up:
            return e_key_prior;
         case XK_Page_Down:
            return e_key_next;
         case XK_Home:
            return e_key_home;
         case XK_End:
            return e_key_end;


      }

      if(keysym >= 'a' && keysym <= 'z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'a');

      }
      else if(keysym >= 'A' && keysym <= 'Z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'A');

      }

      return e_key_none;

   }


} // namespace user
