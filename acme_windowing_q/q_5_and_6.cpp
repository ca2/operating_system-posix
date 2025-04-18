//
// Created by camilo on 2024-12-20 03:22 <3ThomasBorregaardSorensen
// From gtk_3_and_4 by camilo on 2025-01-29 04:50 <3ThomasBorregaardSorensen
//
#include "framework.h"
#include "q_5_and_6.h"
//#include "acme/constant/user_key.h"
//#include <gdk/gdkkeysyms.h>
#include "acme/constant/user_key.h"


namespace q
{


   Qt::Edges as_qt_edges(::experience::enum_frame eframeSizing)
   {

      switch (eframeSizing)
      {
         case ::experience::e_frame_sizing_left:
            return Qt::Edge::LeftEdge;
         case ::experience::e_frame_sizing_top:
            return Qt::Edge::TopEdge;
         case ::experience::e_frame_sizing_right:
            return Qt::Edge::RightEdge;
         case ::experience::e_frame_sizing_bottom:
            return Qt::Edge::BottomEdge;
         case ::experience::e_frame_sizing_top_left:
            return Qt::Edge::LeftEdge | Qt::Edge::TopEdge;
         case ::experience::e_frame_sizing_top_right:
            return Qt::Edge::RightEdge | Qt::Edge::TopEdge;
         case ::experience::e_frame_sizing_bottom_left:
            return Qt::Edge::LeftEdge | Qt::Edge::BottomEdge;
         case ::experience::e_frame_sizing_bottom_right:
            return Qt::Edge::RightEdge | Qt::Edge::BottomEdge;
          default:
              break;
      }
      return {};
   }


   //CLASS_DECL_COMMON_GTK ::user::e_key gtk_key_as_user_ekey(unsigned long long uGtkKey)
   //{
   //
   //   switch(uGtkKey)
   //   {
   //
   //      case GDK_KEY_Delete:
   //         return ::user::e_key_delete;
   //      case GDK_KEY_BackSpace:
   //         return ::user::e_key_back;
   //      case GDK_KEY_Left:
   //         return ::user::e_key_left;
   //      case GDK_KEY_Right:
   //         return ::user::e_key_right;
   //      case GDK_KEY_Up:
   //         return ::user::e_key_up;
   //      case GDK_KEY_Down:
   //         return ::user::e_key_down;
   //      case GDK_KEY_Return:
   //         return ::user::e_key_return;
   //      case GDK_KEY_Tab:
   //         return ::user::e_key_tab;
   //      case GDK_KEY_Shift_L:
   //         return ::user::e_key_left_shift;
   //      case GDK_KEY_Shift_R:
   //         return ::user::e_key_right_shift;
   //      case GDK_KEY_Control_L:
   //         return ::user::e_key_left_control;
   //      case GDK_KEY_Control_R:
   //         return ::user::e_key_right_control;
   //      case GDK_KEY_Alt_L:
   //         return ::user::e_key_left_alt;
   //      case GDK_KEY_Alt_R:
   //         return ::user::e_key_right_alt;
   //      case GDK_KEY_Super_L:
   //         return ::user::e_key_left_command;
   //      case GDK_KEY_Super_R:
   //         return ::user::e_key_right_command;
   //      case GDK_KEY_Page_Down:
   //         return ::user::e_key_page_down;
   //      case GDK_KEY_Page_Up:
   //         return ::user::e_key_page_up;
   //   }
   //   return ::user::e_key_none;
   //
   //
   //}
   //


   ::user::e_key user_key_from_qt_key(int iQtKey)
   {

      switch (iQtKey)
      {
         case Qt::Key_Escape: // 0x01000000
            return ::user::e_key_escape;
         case Qt::Key_Tab: // 0x01000001
            return ::user::e_key_tab;
         case Qt::Key_Backtab: // 0x01000002
            return ::user::e_key_back;
         case Qt::Key_Backspace: // 0x01000003
            return ::user::e_key_back;
         case Qt::Key_Return: // 0x01000004
            return ::user::e_key_return;
         case Qt::Key_Enter: // 0x01000005	Typically located on the keypad.
            return ::user::e_key_return;
         // case Qt::Key_Insert: // 0x01000006
         // case Qt::Key_Delete: // 0x01000007
         // case Qt::Key_Pause: // 0x01000008	The Pause/Break key (Note: Not related to pausing media)
         // case Qt::Key_Print: // 0x01000009
         // case Qt::Key_SysReq: // 0x0100000a
         case Qt::Key_Clear:
         // 0x0100000b	Corresponds to the Clear key on selected Apple keyboard models. On other systems it is commonly mapped to the numeric keypad key 5, when Num Lock is off.
         case Qt::Key_Home: // 0x01000010
            return ::user::e_key_home;
         case Qt::Key_End: // 0x01000011
            return ::user::e_key_home;
         case Qt::Key_Left: // 0x01000012
            return ::user::e_key_left;
         case Qt::Key_Up: // 0x01000013
            return ::user::e_key_up;
         case Qt::Key_Right: // 0x01000014
            return ::user::e_key_right;
         case Qt::Key_Down: // 0x01000015
            return ::user::e_key_down;
         case Qt::Key_PageUp: // 0x01000016
            return ::user::e_key_page_up;
         case Qt::Key_PageDown: // 0x01000017
            return ::user::e_key_page_down;
         case Qt::Key_Shift: // 0x01000020
            return ::user::e_key_shift;
         case Qt::Key_Control: // 0x01000021	On macOS, this corresponds to the Command keys.
            return ::user::e_key_control;
         case Qt::Key_Meta:
            // 0x01000022	On macOS, this corresponds to the Control keys. On Windows keyboards, this key is mapped to the Windows key.
            return ::user::e_key_command;
         case Qt::Key_Alt: // 0x01000023
            return ::user::e_key_alt;
         case Qt::Key_AltGr:
            // 0x01001103	On Windows, when the KeyDown event for this key is sent, the Ctrl+Alt modifiers are also set.
            return ::user::e_key_right_alt;
         // case Qt::Key_CapsLock: // 0x01000024
         //
         // case Qt::Key_NumLock: // 0x01000025
         // case Qt::Key_ScrollLock: // 0x01000026
         case Qt::Key_F1: // 0x01000030
            return ::user::e_key_f1;
         case Qt::Key_F2: // 0x01000031
            return ::user::e_key_f2;
         case Qt::Key_F3: // 0x01000032
            return ::user::e_key_f3;
         case Qt::Key_F4: // 0x01000033
            return ::user::e_key_f4;
         case Qt::Key_F5: // 0x01000034
            return ::user::e_key_f5;
         case Qt::Key_F6: // 0x01000035
            return ::user::e_key_f6;
         case Qt::Key_F7: // 0x01000036
            return ::user::e_key_f7;
         case Qt::Key_F8: // 0x01000037
            return ::user::e_key_f8;
         case Qt::Key_F9: // 0x01000038
            return ::user::e_key_f9;
         case Qt::Key_F10: // 0x01000039
            return ::user::e_key_f10;
         case Qt::Key_F11: // 0x0100003a
            return ::user::e_key_f11;
         case Qt::Key_F12: // 0x0100003b
            return ::user::e_key_f12;
         // case Qt::Key_F13: // 0x0100003c
         // case Qt::Key_F14: // 0x0100003d
         // case Qt::Key_F15: // 0x0100003e
         // case Qt::Key_F16: // 0x0100003f
         // case Qt::Key_F17: // 0x01000040
         // case Qt::Key_F18: // 0x01000041
         // case Qt::Key_F19: // 0x01000042
         // case Qt::Key_F20: // 0x01000043
         // case Qt::Key_F21: // 0x01000044
         // case Qt::Key_F22: // 0x01000045
         // case Qt::Key_F23: // 0x01000046
         // case Qt::Key_F24: // 0x01000047
         // case Qt::Key_F25: // 0x01000048
         // case Qt::Key_F26: // 0x01000049
         // case Qt::Key_F27: // 0x0100004a
         // case Qt::Key_F28: // 0x0100004b
         // case Qt::Key_F29: // 0x0100004c
         // case Qt::Key_F30: // 0x0100004d
         // case Qt::Key_F31: // 0x0100004e
         // case Qt::Key_F32: // 0x0100004f
         // case Qt::Key_F33: // 0x01000050
         // case Qt::Key_F34: // 0x01000051
         // case Qt::Key_F35: // 0x01000052
         case Qt::Key_Super_L: // 0x01000053
            return ::user::e_key_left_command;
         case Qt::Key_Super_R: // 0x01000054
            return ::user::e_key_right;
         // case Qt::Key_Menu: // 0x01000055
         // case Qt::Key_Hyper_L: // 0x01000056
         // case Qt::Key_Hyper_R: // 0x01000057
         // case Qt::Key_Help: // 0x01000058
         // case Qt::Key_Direction_L: // 0x01000059
         // case Qt::Key_Direction_R: // 0x01000060
         case Qt::Key_Space: // 0x20
            return ::user::e_key_space;
         //case Qt::Key_Any	Key_Space
         //case Qt::Key_Exclam: // 0x21
         //   return ::user::e_key_exclamation;
         // case Qt::Key_QuoteDbl: // 0x22
         // case Qt::Key_NumberSign: // 0x23
         // case Qt::Key_Dollar: // 0x24
         // case Qt::Key_Percent: // 0x25
         // case Qt::Key_Ampersand: // 0x26
         // case Qt::Key_Apostrophe: // 0x27
         // case Qt::Key_ParenLeft: // 0x28
         // case Qt::Key_ParenRight: // 0x29
         // case Qt::Key_Asterisk: // 0x2a
         // case Qt::Key_Plus: // 0x2b
         // case Qt::Key_Comma: // 0x2c
         // case Qt::Key_Minus: // 0x2d
         // case Qt::Key_Period: // 0x2e
         // case Qt::Key_Slash: // 0x2f
         case Qt::Key_0: // 0x30
            return ::user::e_key_0;
         case Qt::Key_1: // 0x31
            return ::user::e_key_1;
         case Qt::Key_2: // 0x32
            return ::user::e_key_2;
         case Qt::Key_3: // 0x33
            return ::user::e_key_3;
         case Qt::Key_4: // 0x34
            return ::user::e_key_4;
         case Qt::Key_5: // 0x35
            return ::user::e_key_5;
         case Qt::Key_6: // 0x36
            return ::user::e_key_6;
         case Qt::Key_7: // 0x37
            return ::user::e_key_7;
         case Qt::Key_8: // 0x38
            return ::user::e_key_8;
         case Qt::Key_9: // 0x39
            return ::user::e_key_9;
         // case Qt::Key_Colon: // 0x3a
         //    return ::user::e_key_colon;
         case Qt::Key_Semicolon: // 0x3b
            return ::user::e_key_0;
         // case Qt::Key_Less: // 0x3c
         // case Qt::Key_Equal: // 0x3d
         // case Qt::Key_Greater: // 0x3e
         // case Qt::Key_Question: // 0x3f
         //case Qt::Key_At: // 0x40
         case Qt::Key_A: // 0x41
            return ::user::e_key_a;
         case Qt::Key_B: // 0x42
            return ::user::e_key_b;
         case Qt::Key_C: // 0x43
            return ::user::e_key_c;
         case Qt::Key_D: // 0x44
            return ::user::e_key_d;
         case Qt::Key_E: // 0x45
            return ::user::e_key_e;
         case Qt::Key_F: // 0x46
            return ::user::e_key_f;
         case Qt::Key_G: // 0x47
            return ::user::e_key_g;
         case Qt::Key_H: // 0x48
            return ::user::e_key_h;

         case Qt::Key_I: // 0x49
            return ::user::e_key_i;
         case Qt::Key_J: // 0x4a
            return ::user::e_key_j;
         case Qt::Key_K: // 0x4b
            return ::user::e_key_k;
         case Qt::Key_L: // 0x4c
            return ::user::e_key_l;
         case Qt::Key_M: // 0x4d
            return ::user::e_key_m;
         case Qt::Key_N: // 0x4e
            return ::user::e_key_n;
         case Qt::Key_O: // 0x4f
            return ::user::e_key_o;
         case Qt::Key_P: // 0x50
            return ::user::e_key_p;
         case Qt::Key_Q: // 0x51
            return ::user::e_key_q;
         case Qt::Key_R: // 0x52
            return ::user::e_key_r;
         case Qt::Key_S: // 0x53
            return ::user::e_key_s;
         case Qt::Key_T: // 0x54
            return ::user::e_key_t;
         case Qt::Key_U: // 0x55
            return ::user::e_key_u;
         case Qt::Key_V: // 0x56
            return ::user::e_key_v;
         case Qt::Key_W: // 0x57
            return ::user::e_key_w;
         case Qt::Key_X: // 0x58
            return ::user::e_key_x;
         case Qt::Key_Y: // 0x59
            return ::user::e_key_y;
         case Qt::Key_Z: // 0x5a
            return ::user::e_key_z;
         case Qt::Key_BracketLeft: // 0x5b
            return ::user::e_key_open_bracket;
         case Qt::Key_Backslash: // 0x5c
            return ::user::e_key_backslash;
         case Qt::Key_BracketRight: // 0x5d
            return ::user::e_key_right_bracket;
         case Qt::Key_AsciiCircum: // 0x5e
            // case Qt::Key_Underscore: // 0x5f
            // case Qt::Key_QuoteLeft: // 0x60
            // case Qt::Key_BraceLeft: // 0x7b
            // case Qt::Key_Bar: // 0x7c
            // case Qt::Key_BraceRight: // 0x7d
            // case Qt::Key_AsciiTilde: // 0x7e
            // case Qt::Key_nobreakspace: // 0x0a0
            // case Qt::Key_exclamdown: // 0x0a1
            // case Qt::Key_cent: // 0x0a2
            // case Qt::Key_sterling: // 0x0a3
            // case Qt::Key_currency: // 0x0a4
            // case Qt::Key_yen: // 0x0a5
            // case Qt::Key_brokenbar: // 0x0a6
            // case Qt::Key_section: // 0x0a7
            // case Qt::Key_diaeresis: // 0x0a8
            // case Qt::Key_copyright: // 0x0a9
            // case Qt::Key_ordfeminine: // 0x0aa
            // case Qt::Key_guillemotleft: // 0x0ab
            // case Qt::Key_notsign: // 0x0ac
            // case Qt::Key_hyphen: // 0x0ad
            // case Qt::Key_registered: // 0x0ae
            // case Qt::Key_macron: // 0x0af
            // case Qt::Key_degree: // 0x0b0
            // case Qt::Key_plusminus: // 0x0b1
            // case Qt::Key_twosuperior: // 0x0b2
            // case Qt::Key_threesuperior: // 0x0b3
            // case Qt::Key_acute: // 0x0b4
            // case Qt::Key_micro (since Qt 6.7): // 0x0b5
            // case Qt::Key_mu	Key_micro	Deprecated alias for Key_micro
            // case Qt::Key_paragraph: // 0x0b6
            // case Qt::Key_periodcentered: // 0x0b7
            // case Qt::Key_cedilla: // 0x0b8
            // case Qt::Key_onesuperior: // 0x0b9
            // case Qt::Key_masculine: // 0x0ba
            // case Qt::Key_guillemotright: // 0x0bb
            // case Qt::Key_onequarter: // 0x0bc
            // case Qt::Key_onehalf: // 0x0bd
            // case Qt::Key_threequarters: // 0x0be
            // case Qt::Key_questiondown: // 0x0bf
            // case Qt::Key_Agrave: // 0x0c0
            // case Qt::Key_Aacute: // 0x0c1
            // case Qt::Key_Acircumflex: // 0x0c2
            // case Qt::Key_Atilde: // 0x0c3
            // case Qt::Key_Adiaeresis: // 0x0c4
            // case Qt::Key_Aring: // 0x0c5
            // case Qt::Key_AE: // 0x0c6
            // case Qt::Key_Ccedilla: // 0x0c7
            // case Qt::Key_Egrave: // 0x0c8
            // case Qt::Key_Eacute: // 0x0c9
            // case Qt::Key_Ecircumflex: // 0x0ca
            // case Qt::Key_Ediaeresis: // 0x0cb
            // case Qt::Key_Igrave: // 0x0cc
            // case Qt::Key_Iacute: // 0x0cd
            // case Qt::Key_Icircumflex: // 0x0ce
            // case Qt::Key_Idiaeresis: // 0x0cf
            // case Qt::Key_ETH: // 0x0d0
            // case Qt::Key_Ntilde: // 0x0d1
            // case Qt::Key_Ograve: // 0x0d2
            // case Qt::Key_Oacute: // 0x0d3
            // case Qt::Key_Ocircumflex: // 0x0d4
            // case Qt::Key_Otilde: // 0x0d5
            // case Qt::Key_Odiaeresis: // 0x0d6
            // case Qt::Key_multiply: // 0x0d7
            // case Qt::Key_Ooblique: // 0x0d8
            // case Qt::Key_Ugrave: // 0x0d9
            // case Qt::Key_Uacute: // 0x0da
            // case Qt::Key_Ucircumflex: // 0x0db
            // case Qt::Key_Udiaeresis: // 0x0dc
            // case Qt::Key_Yacute: // 0x0dd
            // case Qt::Key_THORN: // 0x0de
            // case Qt::Key_ssharp: // 0x0df
            // case Qt::Key_division: // 0x0f7
            // case Qt::Key_ydiaeresis: // 0x0ff
            // case Qt::Key_Multi_key: // 0x01001120
            // case Qt::Key_Codeinput: // 0x01001137
            // case Qt::Key_SingleCandidate: // 0x0100113c
            // case Qt::Key_MultipleCandidate: // 0x0100113d
            // case Qt::Key_PreviousCandidate: // 0x0100113e
            // case Qt::Key_Mode_switch: // 0x0100117e
            // case Qt::Key_Kanji: // 0x01001121
            // case Qt::Key_Muhenkan: // 0x01001122
            // case Qt::Key_Henkan: // 0x01001123
            // case Qt::Key_Romaji: // 0x01001124
            // case Qt::Key_Hiragana: // 0x01001125
            // case Qt::Key_Katakana: // 0x01001126
            // case Qt::Key_Hiragana_Katakana: // 0x01001127
            // case Qt::Key_Zenkaku: // 0x01001128
            // case Qt::Key_Hankaku: // 0x01001129
            // case Qt::Key_Zenkaku_Hankaku: // 0x0100112a
            // case Qt::Key_Touroku: // 0x0100112b
            // case Qt::Key_Massyo: // 0x0100112c
            // case Qt::Key_Kana_Lock: // 0x0100112d
            // case Qt::Key_Kana_Shift: // 0x0100112e
            // case Qt::Key_Eisu_Shift: // 0x0100112f
            // case Qt::Key_Eisu_toggle: // 0x01001130
            // case Qt::Key_Hangul: // 0x01001131
            // case Qt::Key_Hangul_Start: // 0x01001132
            // case Qt::Key_Hangul_End: // 0x01001133
            // case Qt::Key_Hangul_Hanja: // 0x01001134
            // case Qt::Key_Hangul_Jamo: // 0x01001135
            // case Qt::Key_Hangul_Romaja: // 0x01001136
            // case Qt::Key_Hangul_Jeonja: // 0x01001138
            // case Qt::Key_Hangul_Banja: // 0x01001139
            // case Qt::Key_Hangul_PreHanja: // 0x0100113a
            // case Qt::Key_Hangul_PostHanja: // 0x0100113b
            // case Qt::Key_Hangul_Special: // 0x0100113f
            // case Qt::Key_Dead_Grave: // 0x01001250
            // case Qt::Key_Dead_Acute: // 0x01001251
            // case Qt::Key_Dead_Circumflex: // 0x01001252
            // case Qt::Key_Dead_Tilde: // 0x01001253
            // case Qt::Key_Dead_Macron: // 0x01001254
            // case Qt::Key_Dead_Breve: // 0x01001255
            // case Qt::Key_Dead_Abovedot: // 0x01001256
            // case Qt::Key_Dead_Diaeresis: // 0x01001257
            // case Qt::Key_Dead_Abovering: // 0x01001258
            // case Qt::Key_Dead_Doubleacute: // 0x01001259
            // case Qt::Key_Dead_Caron: // 0x0100125a
            // case Qt::Key_Dead_Cedilla: // 0x0100125b
            // case Qt::Key_Dead_Ogonek: // 0x0100125c
            // case Qt::Key_Dead_Iota: // 0x0100125d
            // case Qt::Key_Dead_Voiced_Sound: // 0x0100125e
            // case Qt::Key_Dead_Semivoiced_Sound: // 0x0100125f
            // case Qt::Key_Dead_Belowdot: // 0x01001260
            // case Qt::Key_Dead_Hook: // 0x01001261
            // case Qt::Key_Dead_Horn: // 0x01001262
            // case Qt::Key_Dead_Stroke: // 0x01001263
            // case Qt::Key_Dead_Abovecomma: // 0x01001264
            // case Qt::Key_Dead_Abovereversedcomma: // 0x01001265
            // case Qt::Key_Dead_Doublegrave: // 0x01001266
            // case Qt::Key_Dead_Belowring: // 0x01001267
            // case Qt::Key_Dead_Belowmacron: // 0x01001268
            // case Qt::Key_Dead_Belowcircumflex: // 0x01001269
            // case Qt::Key_Dead_Belowtilde: // 0x0100126a
            // case Qt::Key_Dead_Belowbreve: // 0x0100126b
            // case Qt::Key_Dead_Belowdiaeresis: // 0x0100126c
            // case Qt::Key_Dead_Invertedbreve: // 0x0100126d
            // case Qt::Key_Dead_Belowcomma: // 0x0100126e
            // case Qt::Key_Dead_Currency: // 0x0100126f
            // case Qt::Key_Dead_a: // 0x01001280
            // case Qt::Key_Dead_A: // 0x01001281
            // case Qt::Key_Dead_e: // 0x01001282
            // case Qt::Key_Dead_E: // 0x01001283
            // case Qt::Key_Dead_i: // 0x01001284
            // case Qt::Key_Dead_I: // 0x01001285
            // case Qt::Key_Dead_o: // 0x01001286
            // case Qt::Key_Dead_O: // 0x01001287
            // case Qt::Key_Dead_u: // 0x01001288
            // case Qt::Key_Dead_U: // 0x01001289
            // case Qt::Key_Dead_Small_Schwa: // 0x0100128a
            // case Qt::Key_Dead_Capital_Schwa: // 0x0100128b
            // case Qt::Key_Dead_Greek: // 0x0100128c
            // case Qt::Key_Dead_Lowline: // 0x01001290
            // case Qt::Key_Dead_Aboveverticalline: // 0x01001291
            // case Qt::Key_Dead_Belowverticalline: // 0x01001292
            // case Qt::Key_Dead_Longsolidusoverlay: // 0x01001293
            // case Qt::Key_Back: // 0x01000061
            // case Qt::Key_Forward: // 0x01000062
            // case Qt::Key_Stop: // 0x01000063
            // case Qt::Key_Refresh: // 0x01000064
            // case Qt::Key_VolumeDown: // 0x01000070
            // case Qt::Key_VolumeMute: // 0x01000071
            // case Qt::Key_VolumeUp: // 0x01000072
            // case Qt::Key_BassBoost: // 0x01000073
            // case Qt::Key_BassUp: // 0x01000074
            // case Qt::Key_BassDown: // 0x01000075
            // case Qt::Key_TrebleUp: // 0x01000076
            // case Qt::Key_TrebleDown: // 0x01000077
            // case Qt::Key_MediaPlay: // 0x01000080	A key setting the state of the media player to play
            // case Qt::Key_MediaStop: // 0x01000081	A key setting the state of the media player to stop
            // case Qt::Key_MediaPrevious: // 0x01000082
            // case Qt::Key_MediaNext: // 0x01000083
            // case Qt::Key_MediaRecord: // 0x01000084
            // case Qt::Key_MediaPause: // 0x01000085	A key setting the state of the media player to pause (Note: not the pause/break key)
            // case Qt::Key_MediaTogglePlayPause: // 0x01000086	A key to toggle the play/pause state in the media player (rather than setting an absolute state)
            // case Qt::Key_HomePage: // 0x01000090
            // case Qt::Key_Favorites: // 0x01000091
            // case Qt::Key_Search: // 0x01000092
            // case Qt::Key_Standby: // 0x01000093
            // case Qt::Key_OpenUrl: // 0x01000094
            // case Qt::Key_LaunchMail: // 0x010000a0
            // case Qt::Key_LaunchMedia: // 0x010000a1
            // case Qt::Key_Launch0: // 0x010000a2
            // case Qt::Key_Launch1: // 0x010000a3
            // case Qt::Key_Launch2: // 0x010000a4
            // case Qt::Key_Launch3: // 0x010000a5
            // case Qt::Key_Launch4: // 0x010000a6
            // case Qt::Key_Launch5: // 0x010000a7
            // case Qt::Key_Launch6: // 0x010000a8
            // case Qt::Key_Launch7: // 0x010000a9
            // case Qt::Key_Launch8: // 0x010000aa
            // case Qt::Key_Launch9: // 0x010000ab
            // case Qt::Key_LaunchA: // 0x010000ac
            // case Qt::Key_LaunchB: // 0x010000ad
            // case Qt::Key_LaunchC: // 0x010000ae
            // case Qt::Key_LaunchD: // 0x010000af
            // case Qt::Key_LaunchE: // 0x010000b0
            // case Qt::Key_LaunchF: // 0x010000b1
            // case Qt::Key_LaunchG: // 0x0100010e
            // case Qt::Key_LaunchH: // 0x0100010f
            // case Qt::Key_MonBrightnessUp: // 0x010000b2
            // case Qt::Key_MonBrightnessDown: // 0x010000b3
            // case Qt::Key_KeyboardLightOnOff: // 0x010000b4
            // case Qt::Key_KeyboardBrightnessUp: // 0x010000b5
            // case Qt::Key_KeyboardBrightnessDown: // 0x010000b6
            // case Qt::Key_PowerOff: // 0x010000b7
            // case Qt::Key_WakeUp: // 0x010000b8
            // case Qt::Key_Eject: // 0x010000b9
            // case Qt::Key_ScreenSaver: // 0x010000ba
            // case Qt::Key_WWW: // 0x010000bb
            // case Qt::Key_Memo: // 0x010000bc
            // case Qt::Key_LightBulb: // 0x010000bd
            // case Qt::Key_Shop: // 0x010000be
            // case Qt::Key_History: // 0x010000bf
            // case Qt::Key_AddFavorite: // 0x010000c0
            // case Qt::Key_HotLinks: // 0x010000c1
            // case Qt::Key_BrightnessAdjust: // 0x010000c2
            // case Qt::Key_Finance: // 0x010000c3
            // case Qt::Key_Community: // 0x010000c4
            // case Qt::Key_AudioRewind: // 0x010000c5
            // case Qt::Key_BackForward: // 0x010000c6
            // case Qt::Key_ApplicationLeft: // 0x010000c7
            // case Qt::Key_ApplicationRight: // 0x010000c8
            // case Qt::Key_Book: // 0x010000c9
            // case Qt::Key_CD: // 0x010000ca
            // case Qt::Key_Calculator: // 0x010000cb
            // case Qt::Key_ToDoList: // 0x010000cc
            // case Qt::Key_ClearGrab: // 0x010000cd
            // case Qt::Key_Close: // 0x010000ce
            // case Qt::Key_Copy: // 0x010000cf
            // case Qt::Key_Cut: // 0x010000d0
            // case Qt::Key_Display: // 0x010000d1
            // case Qt::Key_DOS: // 0x010000d2
            // case Qt::Key_Documents: // 0x010000d3
            // case Qt::Key_Excel: // 0x010000d4
            // case Qt::Key_Explorer: // 0x010000d5
            // case Qt::Key_Game: // 0x010000d6
            // case Qt::Key_Go: // 0x010000d7
            // case Qt::Key_iTouch: // 0x010000d8
            // case Qt::Key_LogOff: // 0x010000d9
            // case Qt::Key_Market: // 0x010000da
            // case Qt::Key_Meeting: // 0x010000db
            // case Qt::Key_MenuKB: // 0x010000dc
            // case Qt::Key_MenuPB: // 0x010000dd
            // case Qt::Key_MySites: // 0x010000de
            // case Qt::Key_News: // 0x010000df
            // case Qt::Key_OfficeHome: // 0x010000e0
            // case Qt::Key_Option: // 0x010000e1
            // case Qt::Key_Paste: // 0x010000e2
            // case Qt::Key_Phone: // 0x010000e3
            // case Qt::Key_Calendar: // 0x010000e4
            // case Qt::Key_Reply: // 0x010000e5
            // case Qt::Key_Reload: // 0x010000e6
            // case Qt::Key_RotateWindows: // 0x010000e7
            // case Qt::Key_RotationPB: // 0x010000e8
            // case Qt::Key_RotationKB: // 0x010000e9
            // case Qt::Key_Save: // 0x010000ea
            // case Qt::Key_Send: // 0x010000eb
            // case Qt::Key_Spell: // 0x010000ec
            // case Qt::Key_SplitScreen: // 0x010000ed
            // case Qt::Key_Support: // 0x010000ee
            // case Qt::Key_TaskPane: // 0x010000ef
            // case Qt::Key_Terminal: // 0x010000f0
            // case Qt::Key_Tools: // 0x010000f1
            // case Qt::Key_Travel: // 0x010000f2
            // case Qt::Key_Video: // 0x010000f3
            // case Qt::Key_Word: // 0x010000f4
            // case Qt::Key_Xfer: // 0x010000f5
            // case Qt::Key_ZoomIn: // 0x010000f6
            // case Qt::Key_ZoomOut: // 0x010000f7
            // case Qt::Key_Away: // 0x010000f8
            // case Qt::Key_Messenger: // 0x010000f9
            // case Qt::Key_WebCam: // 0x010000fa
            // case Qt::Key_MailForward: // 0x010000fb
            // case Qt::Key_Pictures: // 0x010000fc
            // case Qt::Key_Music: // 0x010000fd
            // case Qt::Key_Battery: // 0x010000fe
            // case Qt::Key_Bluetooth: // 0x010000ff
            // case Qt::Key_WLAN: // 0x01000100
            // case Qt::Key_UWB: // 0x01000101
            // case Qt::Key_AudioForward: // 0x01000102
            // case Qt::Key_AudioRepeat: // 0x01000103
            // case Qt::Key_AudioRandomPlay: // 0x01000104
            // case Qt::Key_Subtitle: // 0x01000105
            // case Qt::Key_AudioCycleTrack: // 0x01000106
            // case Qt::Key_Time: // 0x01000107
            // case Qt::Key_Hibernate: // 0x01000108
            // case Qt::Key_View: // 0x01000109
            // case Qt::Key_TopMenu: // 0x0100010a
            // case Qt::Key_PowerDown: // 0x0100010b
            // case Qt::Key_Suspend: // 0x0100010c
            // case Qt::Key_ContrastAdjust: // 0x0100010d
            // case Qt::Key_TouchpadToggle: // 0x01000110
            // case Qt::Key_TouchpadOn: // 0x01000111
            // case Qt::Key_TouchpadOff: // 0x01000112
            // case Qt::Key_MicMute: // 0x01000113
            // case Qt::Key_Red: // 0x01000114
            // case Qt::Key_Green: // 0x01000115
            // case Qt::Key_Yellow: // 0x01000116
            // case Qt::Key_Blue: // 0x01000117
            // case Qt::Key_ChannelUp: // 0x01000118
            // case Qt::Key_ChannelDown: // 0x01000119
            // case Qt::Key_Guide: // 0x0100011a
            // case Qt::Key_Info: // 0x0100011b
            // case Qt::Key_Settings: // 0x0100011c
            // case Qt::Key_MicVolumeUp: // 0x0100011d
            // case Qt::Key_MicVolumeDown: // 0x0100011e
            // case Qt::Key_New: // 0x01000120
            // case Qt::Key_Open: // 0x01000121
            // case Qt::Key_Find: // 0x01000122
            // case Qt::Key_Undo: // 0x01000123
            // case Qt::Key_Redo: // 0x01000124
            // case Qt::Key_MediaLast: // 0x0100ffff
            // case Qt::Key_unknown: // 0x01ffffff
            // case Qt::Key_Call: // 0x01100004	A key to answer or initiate a call (see case Qt::Key_ToggleCallHangup for a key to toggle current call state)
            // case Qt::Key_Camera: // 0x01100020	A key to activate the camera shutter. On Windows Runtime, the environment variable QT_QPA_ENABLE_CAMERA_KEYS must be set to receive the event.
            // case Qt::Key_CameraFocus: // 0x01100021	A key to focus the camera. On Windows Runtime, the environment variable QT_QPA_ENABLE_CAMERA_KEYS must be set to receive the event.
            // case Qt::Key_Context1: // 0x01100000
            // case Qt::Key_Context2: // 0x01100001
            // case Qt::Key_Context3: // 0x01100002
            // case Qt::Key_Context4: // 0x01100003
            // case Qt::Key_Flip: // 0x01100006
            // case Qt::Key_Hangup: // 0x01100005	A key to end an ongoing call (see case Qt::Key_ToggleCallHangup for a key to toggle current call state)
            // case Qt::Key_No: // 0x01010002
            // case Qt::Key_Select: // 0x01010000
            // case Qt::Key_Yes: // 0x01010001
            // case Qt::Key_ToggleCallHangup: // 0x01100007	A key to toggle the current call state (ie. either answer, or hangup) depending on current call state
            // case Qt::Key_VoiceDial: // 0x01100008
            // case Qt::Key_LastNumberRedial: // 0x01100009
            // case Qt::Key_Execute: // 0x01020003
            // case Qt::Key_Printer: // 0x01020002
            // case Qt::Key_Play: // 0x01020005
            // case Qt::Key_Sleep: // 0x01020004
            // case Qt::Key_Zoom: // 0x01020006
            // case Qt::Key_Exit: // 0x0102000a
            // case Qt::Key_Cancel
         default:
            //throw ::exception(error_wrong_state);
            return ::user::e_key_none;
      }

   }


}
