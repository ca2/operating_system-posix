//
// Created by camilo on 2024-12-20 03:22 <3ThomasBorregaardSorensen
//
#include "framework.h"
#include "acme/constant/user_key.h"
#include <gdk/gdkkeysyms.h>


// CLASS_DECL_ACME_WINDOWING_G ::user::e_key gtk_key_as_user_ekey(::u64 uGtkKey)
// {
//
//    switch(uGtkKey)
//    {
//
//       case GDK_KEY_Delete:
//          return ::user::e_key_delete;
//       case GDK_KEY_BackSpace:
//          return ::user::e_key_back;
//       case GDK_KEY_Left:
//          return ::user::e_key_left;
//       case GDK_KEY_Right:
//          return ::user::e_key_right;
//       case GDK_KEY_Up:
//          return ::user::e_key_up;
//       case GDK_KEY_Down:
//          return ::user::e_key_down;
//       case GDK_KEY_Return:
//          return ::user::e_key_return;
//       case GDK_KEY_Tab:
//          return ::user::e_key_tab;
//       case GDK_KEY_Shift_L:
//          return ::user::e_key_left_shift;
//       case GDK_KEY_Shift_R:
//          return ::user::e_key_right_shift;
//       case GDK_KEY_Control_L:
//          return ::user::e_key_left_control;
//       case GDK_KEY_Control_R:
//          return ::user::e_key_right_control;
//       case GDK_KEY_Alt_L:
//          return ::user::e_key_left_alt;
//       case GDK_KEY_Alt_R:
//          return ::user::e_key_right_alt;
//       case GDK_KEY_Super_L:
//          return ::user::e_key_left_command;
//       case GDK_KEY_Super_R:
//          return ::user::e_key_right_command;
//       case GDK_KEY_Page_Down:
//          return ::user::e_key_page_down;
//       case GDK_KEY_Page_Up:
//          return ::user::e_key_page_up;
//    }
//    return ::user::e_key_none;
//
//
// }


#include "framework.h"
#include "acme/constant/user_key.h"

#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>


CLASS_DECL_ACME_WINDOWING_G
::user::e_key gtk_key_as_user_ekey(::u64 uGtkKey)
{

   const auto keyval = (guint)uGtkKey;

   // This handles both GDK_KEY_a and GDK_KEY_A.
   const auto keyvalLower = gdk_keyval_to_lower(keyval);


   // Alphabetic keys are contiguous in both GDK and ::user::enum_key.
   if (keyvalLower >= GDK_KEY_a && keyvalLower <= GDK_KEY_z)
   {

      return (::user::enum_key)
         (
            (int)::user::e_key_a
            + (int)(keyvalLower - GDK_KEY_a)
         );

   }


   // Main keyboard numeric keys.
   if (keyval >= GDK_KEY_0 && keyval <= GDK_KEY_9)
   {

      return (::user::enum_key)
         (
            (int)::user::e_key_0
            + (int)(keyval - GDK_KEY_0)
         );

   }


   // Numeric keypad digits, when Num Lock produces numeric keyvals.
   if (keyval >= GDK_KEY_KP_0 && keyval <= GDK_KEY_KP_9)
   {

      return (::user::enum_key)
         (
            (int)::user::e_key_numpad_0
            + (int)(keyval - GDK_KEY_KP_0)
         );

   }


   // Function keys are also contiguous.
   if (keyval >= GDK_KEY_F1 && keyval <= GDK_KEY_F24)
   {

      return (::user::enum_key)
         (
            (int)::user::e_key_f1
            + (int)(keyval - GDK_KEY_F1)
         );

   }


   switch (keyval)
   {

      // -------------------------------------------------------------------
      // Editing and basic control keys
      // -------------------------------------------------------------------

      case GDK_KEY_BackSpace:
         return ::user::e_key_back;

      case GDK_KEY_Delete:
         return ::user::e_key_delete;

      case GDK_KEY_Insert:
         return ::user::e_key_insert;

      case GDK_KEY_Return:
      case GDK_KEY_Linefeed:
#ifdef GDK_KEY_ISO_Enter
      case GDK_KEY_ISO_Enter:
#endif
         return ::user::e_key_return;

      case GDK_KEY_Tab:
      case GDK_KEY_ISO_Left_Tab:
         return ::user::e_key_tab;

      case GDK_KEY_Escape:
         return ::user::e_key_escape;

      case GDK_KEY_space:
         return ::user::e_key_space;

      case GDK_KEY_Clear:
         return ::user::e_key_clear;


      // -------------------------------------------------------------------
      // Navigation
      // -------------------------------------------------------------------

      case GDK_KEY_Left:
         return ::user::e_key_left;

      case GDK_KEY_Right:
         return ::user::e_key_right;

      case GDK_KEY_Up:
         return ::user::e_key_up;

      case GDK_KEY_Down:
         return ::user::e_key_down;

      case GDK_KEY_Page_Up:
         return ::user::e_key_page_up;

      case GDK_KEY_Page_Down:
         return ::user::e_key_page_down;

      case GDK_KEY_Home:
         return ::user::e_key_home;

      case GDK_KEY_End:
         return ::user::e_key_end;

      case GDK_KEY_Begin:
         return ::user::e_key_clear;


      // -------------------------------------------------------------------
      // Modifier keys
      // -------------------------------------------------------------------

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

#ifdef GDK_KEY_ISO_Level3_Shift
      case GDK_KEY_ISO_Level3_Shift:
         // Usually AltGr.
         return ::user::e_key_right_alt;
#endif

      case GDK_KEY_Meta_L:
      case GDK_KEY_Super_L:
         return ::user::e_key_left_command;

      case GDK_KEY_Meta_R:
      case GDK_KEY_Super_R:
         return ::user::e_key_right_command;

      case GDK_KEY_Mode_switch:
         return ::user::e_key_mode;


      // -------------------------------------------------------------------
      // Lock keys
      // -------------------------------------------------------------------

      case GDK_KEY_Caps_Lock:
         return ::user::e_key_capslock;

      case GDK_KEY_Num_Lock:
         return ::user::e_key_numlock;

      case GDK_KEY_Scroll_Lock:
         return ::user::e_key_scroll_lock;


      // -------------------------------------------------------------------
      // Numeric keypad
      // -------------------------------------------------------------------

      case GDK_KEY_KP_Enter:
         return ::user::e_key_numpad_enter;

      case GDK_KEY_KP_Add:
         return ::user::e_key_numpad_plus;

      case GDK_KEY_KP_Subtract:
         return ::user::e_key_numpad_minus;

      case GDK_KEY_KP_Multiply:
         return ::user::e_key_numpad_multiply;

      case GDK_KEY_KP_Divide:
         return ::user::e_key_numpad_divide;

      case GDK_KEY_KP_Equal:
         return ::user::e_key_numpad_equal;

      case GDK_KEY_KP_Decimal:
         return ::user::e_key_numpad_period;

      case GDK_KEY_KP_Separator:
         return ::user::e_key_separator;

      case GDK_KEY_KP_Space:
         return ::user::e_key_space;

      case GDK_KEY_KP_Tab:
         return ::user::e_key_tab;


      // Keypad navigation values produced while Num Lock is disabled.

      case GDK_KEY_KP_Left:
         return ::user::e_key_left;

      case GDK_KEY_KP_Right:
         return ::user::e_key_right;

      case GDK_KEY_KP_Up:
         return ::user::e_key_up;

      case GDK_KEY_KP_Down:
         return ::user::e_key_down;

      case GDK_KEY_KP_Home:
         return ::user::e_key_home;

      case GDK_KEY_KP_End:
         return ::user::e_key_end;

      case GDK_KEY_KP_Page_Up:
         return ::user::e_key_page_up;

      case GDK_KEY_KP_Page_Down:
         return ::user::e_key_page_down;

      case GDK_KEY_KP_Insert:
         return ::user::e_key_insert;

      case GDK_KEY_KP_Delete:
         return ::user::e_key_delete;

      case GDK_KEY_KP_Begin:
         return ::user::e_key_clear;

      case GDK_KEY_KP_F1:
         return ::user::e_key_f1;

      case GDK_KEY_KP_F2:
         return ::user::e_key_f2;

      case GDK_KEY_KP_F3:
         return ::user::e_key_f3;

      case GDK_KEY_KP_F4:
         return ::user::e_key_f4;


      // -------------------------------------------------------------------
      // Main keyboard punctuation
      // -------------------------------------------------------------------

      case GDK_KEY_semicolon:
      case GDK_KEY_colon:
         return ::user::e_key_semicolon;

      case GDK_KEY_comma:
      case GDK_KEY_less:
         return ::user::e_key_comma;

      case GDK_KEY_period:
      case GDK_KEY_greater:
         return ::user::e_key_dot;

      case GDK_KEY_minus:
      case GDK_KEY_underscore:
         return ::user::e_key_hyphen;

      case GDK_KEY_equal:
         return ::user::e_key_equal;

      case GDK_KEY_plus:
         return ::user::e_key_plus;

      case GDK_KEY_slash:
      case GDK_KEY_question:
         return ::user::e_key_slash;

      case GDK_KEY_backslash:
      case GDK_KEY_bar:
         return ::user::e_key_backslash;

      case GDK_KEY_bracketleft:
      case GDK_KEY_braceleft:
         return ::user::e_key_open_bracket;

      case GDK_KEY_bracketright:
      case GDK_KEY_braceright:
         return ::user::e_key_close_bracket;

      case GDK_KEY_grave:
      case GDK_KEY_dead_grave:
         return ::user::e_key_grave;

      case GDK_KEY_asciitilde:
      case GDK_KEY_dead_tilde:
         return ::user::e_key_til;

      case GDK_KEY_apostrophe:
      case GDK_KEY_quotedbl:
         return ::user::e_key_apostrophe;

      case GDK_KEY_acute:
      case GDK_KEY_dead_acute:
         return ::user::e_key_acute;


      // -------------------------------------------------------------------
      // Shifted number-row symbols
      //
      // These mappings are useful for US-like layouts, where Shift+1
      // produces GDK_KEY_exclam instead of GDK_KEY_1.
      // -------------------------------------------------------------------

      case GDK_KEY_exclam:
         return ::user::e_key_1;

      case GDK_KEY_at:
         return ::user::e_key_2;

      case GDK_KEY_numbersign:
         return ::user::e_key_3;

      case GDK_KEY_dollar:
         return ::user::e_key_4;

      case GDK_KEY_percent:
         return ::user::e_key_5;

      case GDK_KEY_asciicircum:
         return ::user::e_key_6;

      case GDK_KEY_ampersand:
         return ::user::e_key_7;

      case GDK_KEY_asterisk:
         return ::user::e_key_8;

      case GDK_KEY_parenleft:
         return ::user::e_key_9;

      case GDK_KEY_parenright:
         return ::user::e_key_0;


      // -------------------------------------------------------------------
      // System and application keys
      // -------------------------------------------------------------------

      case GDK_KEY_Print:
         return ::user::e_key_print_screen;

      case GDK_KEY_Sys_Req:
         return ::user::e_key_sysreq;

      case GDK_KEY_Pause:
      case GDK_KEY_Break:
         return ::user::e_key_pause;

      case GDK_KEY_Menu:
         return ::user::e_key_application;

      case GDK_KEY_Select:
         return ::user::e_key_select;

      case GDK_KEY_Execute:
         return ::user::e_key_execute;

      case GDK_KEY_Cancel:
         return ::user::e_key_cancel;

      case GDK_KEY_Help:
         return ::user::e_key_help;

      case GDK_KEY_Find:
         return ::user::e_key_find;

      case GDK_KEY_Undo:
         return ::user::e_key_undo;

      case GDK_KEY_Redo:
         return ::user::e_key_again;

#ifdef GDK_KEY_Again
      case GDK_KEY_Again:
         return ::user::e_key_again;
#endif

#ifdef GDK_KEY_Hangul
      case GDK_KEY_Hangul:
         return ::user::e_key_hangul;
#endif


      // -------------------------------------------------------------------
      // Clipboard keys
      // -------------------------------------------------------------------

#ifdef GDK_KEY_Copy
      case GDK_KEY_Copy:
         return ::user::e_key_copy;
#endif

#ifdef GDK_KEY_Cut
      case GDK_KEY_Cut:
         return ::user::e_key_cut;
#endif

#ifdef GDK_KEY_Paste
      case GDK_KEY_Paste:
         return ::user::e_key_paste;
#endif


      // -------------------------------------------------------------------
      // Display and keyboard brightness
      // -------------------------------------------------------------------

#ifdef GDK_KEY_MonBrightnessDown
      case GDK_KEY_MonBrightnessDown:
         return ::user::e_key_brightness_down;
#endif

#ifdef GDK_KEY_MonBrightnessUp
      case GDK_KEY_MonBrightnessUp:
         return ::user::e_key_brightness_up;
#endif

#ifdef GDK_KEY_KbdLightOnOff
      case GDK_KEY_KbdLightOnOff:
         return ::user::e_key_kbdillumtoggle;
#endif

#ifdef GDK_KEY_KbdBrightnessDown
      case GDK_KEY_KbdBrightnessDown:
         return ::user::e_key_kbdillumdown;
#endif

#ifdef GDK_KEY_KbdBrightnessUp
      case GDK_KEY_KbdBrightnessUp:
         return ::user::e_key_kbdillumup;
#endif

#ifdef GDK_KEY_Display
      case GDK_KEY_Display:
         return ::user::e_key_display_switch;
#endif


      // -------------------------------------------------------------------
      // Audio and multimedia
      // -------------------------------------------------------------------

#ifdef GDK_KEY_AudioMute
      case GDK_KEY_AudioMute:
         return ::user::e_key_mute;
#endif

#ifdef GDK_KEY_AudioLowerVolume
      case GDK_KEY_AudioLowerVolume:
         return ::user::e_key_volume_down;
#endif

#ifdef GDK_KEY_AudioRaiseVolume
      case GDK_KEY_AudioRaiseVolume:
         return ::user::e_key_volume_up;
#endif

#ifdef GDK_KEY_AudioPlay
      case GDK_KEY_AudioPlay:
         return ::user::e_key_audioplay;
#endif

#ifdef GDK_KEY_AudioPause
      case GDK_KEY_AudioPause:
         return ::user::e_key_audioplay;
#endif

#ifdef GDK_KEY_AudioStop
      case GDK_KEY_AudioStop:
         return ::user::e_key_audiostop;
#endif

#ifdef GDK_KEY_AudioPrev
      case GDK_KEY_AudioPrev:
         return ::user::e_key_audioprev;
#endif

#ifdef GDK_KEY_AudioNext
      case GDK_KEY_AudioNext:
         return ::user::e_key_audionext;
#endif

#ifdef GDK_KEY_AudioRewind
      case GDK_KEY_AudioRewind:
         return ::user::e_key_audiorewind;
#endif

#ifdef GDK_KEY_AudioMedia
      case GDK_KEY_AudioMedia:
         return ::user::e_key_media_select;
#endif

#ifdef GDK_KEY_Eject
      case GDK_KEY_Eject:
         return ::user::e_key_eject;
#endif


      // -------------------------------------------------------------------
      // Browser and Internet keys
      // -------------------------------------------------------------------

#ifdef GDK_KEY_Back
      case GDK_KEY_Back:
         return ::user::e_key_ac_back;
#endif

#ifdef GDK_KEY_Forward
      case GDK_KEY_Forward:
         return ::user::e_key_ac_forward;
#endif

#ifdef GDK_KEY_Refresh
      case GDK_KEY_Refresh:
         return ::user::e_key_ac_refresh;
#endif

#ifdef GDK_KEY_Stop
      case GDK_KEY_Stop:
         return ::user::e_key_stop;
#endif

#ifdef GDK_KEY_Search
      case GDK_KEY_Search:
         return ::user::e_key_ac_search;
#endif

#ifdef GDK_KEY_Favorites
      case GDK_KEY_Favorites:
         return ::user::e_key_ac_bookmarks;
#endif

#ifdef GDK_KEY_HomePage
      case GDK_KEY_HomePage:
         return ::user::e_key_ac_home;
#endif

#ifdef GDK_KEY_WWW
      case GDK_KEY_WWW:
         return ::user::e_key_www;
#endif

#ifdef GDK_KEY_Mail
      case GDK_KEY_Mail:
         return ::user::e_key_mail;
#endif

#ifdef GDK_KEY_MyComputer
      case GDK_KEY_MyComputer:
         return ::user::e_key_computer;
#endif

#ifdef GDK_KEY_Calculator
      case GDK_KEY_Calculator:
         return ::user::e_key_calculator;
#endif


      // -------------------------------------------------------------------
      // Power and launch keys
      // -------------------------------------------------------------------

#ifdef GDK_KEY_PowerOff
      case GDK_KEY_PowerOff:
         return ::user::e_key_power;
#endif

#ifdef GDK_KEY_PowerDown
      case GDK_KEY_PowerDown:
         return ::user::e_key_power;
#endif

#ifdef GDK_KEY_Sleep
      case GDK_KEY_Sleep:
         return ::user::e_key_sleep;
#endif

#ifdef GDK_KEY_Standby
      case GDK_KEY_Standby:
         return ::user::e_key_sleep;
#endif

#ifdef GDK_KEY_Launch1
      case GDK_KEY_Launch1:
         return ::user::e_key_app1;
#endif

#ifdef GDK_KEY_Launch2
      case GDK_KEY_Launch2:
         return ::user::e_key_app2;
#endif

      default:
         break;

   }


   return ::user::e_key_none;

}