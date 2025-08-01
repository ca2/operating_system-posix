//
// Created by camilo on 15/02/2021. 22:00 BRT <3TBS_!!
// from aura/user/keyboard
//
#include "framework.h"
#include "keyboard.h"
#include "acme/constant/user_key.h"
//#include "windowing_system_x11/keyboard.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/input/input.h"
#include "apex/platform/system.h"
//#include "apex/user/user/prototype.h"
#include "acme/user/user/key.h"
#include "apex/user/user/interaction_base.h"
//#include "windowing_system_wayland/xkb_input.h"
//#include <wayland-server-protocol.h>
//#include <xkbcommon/xkbcommon.h>
//#include <sys/mman.h>
//#include <unistd.h>

//#if defined(LINUX) || defined(SOLARIS)
////#include "base/base/os/x11/x11_keyboard.h"
//string x11_keyboard_get_current_group_symbol();
//#elif defined(MACOS)
//string keyboard_input_source();
//#endif


namespace windowing_q
{


#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

//   CLASS_DECL_AURA ::user::enum_key keysym_to_userkey(const lparam & lparam);

#elif defined(MACOS)

   CLASS_DECL_AURA ::user::enum_key vkcode_to_userkey(wparam wparam);

#endif


   keyboard::keyboard()
   {

//      m_pxkbkeymap = nullptr;
//      m_pxkbstate = nullptr;

   }


   keyboard::~keyboard()
   {

//      if(m_pxkbcontext)
//      {
//
//         ::xkb_context_unref(m_pxkbcontext);
//
//         m_pxkbcontext = nullptr;
//
//      }

   }


   void keyboard::enum_init(::platform::system * psystem)
   {

//      SET_ENUM_TEXT(::user::e_key_0);
//      SET_ENUM_TEXT(::user::e_key_1);
//      SET_ENUM_TEXT(::user::e_key_2);
//      SET_ENUM_TEXT(::user::e_key_3);
//      SET_ENUM_TEXT(::user::e_key_4);
//      SET_ENUM_TEXT(::user::e_key_5);
//      SET_ENUM_TEXT(::user::e_key_6);
//      SET_ENUM_TEXT(::user::e_key_7);
//      SET_ENUM_TEXT(::user::e_key_8);
//      SET_ENUM_TEXT(::user::e_key_9);
//      SET_ENUM_TEXT(::user::e_key_a);
//      SET_ENUM_TEXT(::user::e_key_b);
//      SET_ENUM_TEXT(::user::e_key_c);
//      SET_ENUM_TEXT(::user::e_key_d);
//      SET_ENUM_TEXT(::user::e_key_e);
//      SET_ENUM_TEXT(::user::e_key_f);
//      SET_ENUM_TEXT(::user::e_key_g);
//      SET_ENUM_TEXT(::user::e_key_h);
//      SET_ENUM_TEXT(::user::e_key_i);
//      SET_ENUM_TEXT(::user::e_key_j);
//      SET_ENUM_TEXT(::user::e_key_k);
//      SET_ENUM_TEXT(::user::e_key_l);
//      SET_ENUM_TEXT(::user::e_key_m);
//      SET_ENUM_TEXT(::user::e_key_n);
//      SET_ENUM_TEXT(::user::e_key_o);
//      SET_ENUM_TEXT(::user::e_key_p);
//      SET_ENUM_TEXT(::user::e_key_q);
//      SET_ENUM_TEXT(::user::e_key_r);
//      SET_ENUM_TEXT(::user::e_key_s);
//      SET_ENUM_TEXT(::user::e_key_t);
//      SET_ENUM_TEXT(::user::e_key_u);
//      SET_ENUM_TEXT(::user::e_key_v);
//      SET_ENUM_TEXT(::user::e_key_w);
//      SET_ENUM_TEXT(::user::e_key_x);
//      SET_ENUM_TEXT(::user::e_key_y);
//      SET_ENUM_TEXT(::user::e_key_z);
//      SET_ENUM_TEXT(::user::e_key_semicolon);
//      SET_ENUM_TEXT(::user::e_key_semicolon2);
//      SET_ENUM_TEXT(::user::e_key_comma);
//      SET_ENUM_TEXT(::user::e_key_dot);
//      SET_ENUM_TEXT(::user::e_key_shift);
//      SET_ENUM_TEXT(::user::e_key_left_shift);
//      SET_ENUM_TEXT(::user::e_key_right_shift);
//      SET_ENUM_TEXT(::user::e_key_control);
//      SET_ENUM_TEXT(::user::e_key_left_control);
//      SET_ENUM_TEXT(::user::e_key_right_control);
//      SET_ENUM_TEXT(::user::e_key_alt);
//      SET_ENUM_TEXT(::user::e_key_left_alt);
//      SET_ENUM_TEXT(::user::e_key_right_alt);
//      SET_ENUM_TEXT(::user::e_key_command);
//      SET_ENUM_TEXT(::user::e_key_left_command);
//      SET_ENUM_TEXT(::user::e_key_right_command);
//      SET_ENUM_TEXT(::user::e_key_left_button);
//      SET_ENUM_TEXT(::user::e_key_middle_button);
//      SET_ENUM_TEXT(::user::e_key_right_button);
//      SET_ENUM_TEXT(::user::e_key_back);
//      SET_ENUM_TEXT(::user::e_key_delete);
//      SET_ENUM_TEXT(::user::e_key_space);
//      SET_ENUM_TEXT(::user::e_key_right);
//      SET_ENUM_TEXT(::user::e_key_down);
//      SET_ENUM_TEXT(::user::e_key_left);
//      SET_ENUM_TEXT(::user::e_key_up);
//      SET_ENUM_TEXT(::user::e_key_prior);
//      SET_ENUM_TEXT(::user::e_key_next);
//      SET_ENUM_TEXT(::user::e_key_return);
//      SET_ENUM_TEXT(::user::e_key_home);
//      SET_ENUM_TEXT(::user::e_key_end);
//      SET_ENUM_TEXT(::user::e_key_tab);
//      SET_ENUM_TEXT(::user::e_key_capslock);
//      SET_ENUM_TEXT(::user::e_key_hyphen);
//      SET_ENUM_TEXT(::user::e_key_semicolon3);
//      SET_ENUM_TEXT(::user::e_key_slash2);
//      SET_ENUM_TEXT(::user::e_key_backslash2);
//      SET_ENUM_TEXT(::user::e_key_closebracket2);
//      SET_ENUM_TEXT(::user::e_key_openbracket2);
//      SET_ENUM_TEXT(::user::e_key_til2);
//      SET_ENUM_TEXT(::user::e_key_acute2);
//      SET_ENUM_TEXT(::user::e_key_equal);
//      SET_ENUM_TEXT(::user::e_key_escape);
//      SET_ENUM_TEXT(::user::e_key_apostrophe2);
//      SET_ENUM_TEXT(::user::e_key_numpad_0);
//      SET_ENUM_TEXT(::user::e_key_numpad_1);
//      SET_ENUM_TEXT(::user::e_key_numpad_2);
//      SET_ENUM_TEXT(::user::e_key_numpad_3);
//      SET_ENUM_TEXT(::user::e_key_numpad_4);
//      SET_ENUM_TEXT(::user::e_key_numpad_5);
//      SET_ENUM_TEXT(::user::e_key_numpad_6);
//      SET_ENUM_TEXT(::user::e_key_numpad_7);
//      SET_ENUM_TEXT(::user::e_key_numpad_8);
//      SET_ENUM_TEXT(::user::e_key_numpad_9);
//      SET_ENUM_TEXT(::user::e_key_print_screen);
//      SET_ENUM_TEXT(::user::e_key_f1);
//      SET_ENUM_TEXT(::user::e_key_f2);
//      SET_ENUM_TEXT(::user::e_key_f3);
//      SET_ENUM_TEXT(::user::e_key_f4);
//      SET_ENUM_TEXT(::user::e_key_f5);
//      SET_ENUM_TEXT(::user::e_key_f6);
//      SET_ENUM_TEXT(::user::e_key_f7);
//      SET_ENUM_TEXT(::user::e_key_f8);
//      SET_ENUM_TEXT(::user::e_key_f9);
//      SET_ENUM_TEXT(::user::e_key_f10);
//      SET_ENUM_TEXT(::user::e_key_f11);
//      SET_ENUM_TEXT(::user::e_key_f12);

   }


   void keyboard::initialize(::particle * pparticle)
   {

      //auto estatus =
      //
      ::object::initialize(pparticle);

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }

      enum_init(system());

//      m_pxkbcontext = xkb_context_new({});
//
//      if(!m_pxkbcontext)
//      {
//
//         throw ::exception(error_failed, "Failed to xkb_context_new");
//
//      }

      //return ::success;

//      string strFile;
//
//#ifdef MACOS
//
//      strFile = Context.directory()->matter("keyboard/windows/default.xml");
//
//#elif defined( LINUX)
//
//    return true;
//
//      strFile = Context.directory()->matter("keyboard/freebsd/default.xml");
//
//#elif defined(__APPLE__)
//
//      strFile = Context.directory()->matter("keyboard/macos/default.xml");
//
//#elif defined(__ANDROID__)
//
//      //strPath = Context.directory()->matter("keyboard/android/default.xml");
//
//      strFile = Context.directory()->matter("keyboard/windows/default.xml");
//
//#else
//
//#ifndef UNIVERSAL_WINDOWS
//
//      WCHAR wsz[KL_NAMELENGTH];
//
//      unsigned short w;
//
//      if(GetKeyboardLayoutNameW(wsz))
//      {
//
//         if(wcslen(wsz) == 8)
//         {
//
//            ::collection::index i = 0;
//
//            for(; i < 8; i++)
//            {
//               if(!unicode_is_digit(wsz[i]) && !(wsz[i] >= 'A' && wsz[i] <= 'F') && !(wsz[i] >= 'a' && wsz[i] <= 'f'))
//                  break;
//            }
//
//            if(i == 8)
//            {
//               string str(wstring(&wsz[4],4)); // least significant four digits
//
//               w = (unsigned short) ::hex::to_long_long(str);
//
//            }
//
//         }
//         else
//         {
//
//            HKL hkl = GetKeyboardLayout(::GetCurrentThreadId());
//
//            w = HIWORD(hkl);
//
//            w &= 0x0fff;
//
//         }
//
//      }
//
//      string str = as_string(w);
//
//      //strFile = Context.directory()->matter("keyboard/windows/" + str + ".xml");
//
//      //if(Context.file()->exists(strFile))
//      //{
//
//      //   if (load_os_layout(strFile))
//      //   {
//
//      //      return true;
//
//      //   }
//
//      //}
//
//#endif
//
//      strFile = Context.directory()->matter("keyboard/windows/default.xml");
//
//#endif
//
//      if (!load_os_layout(strFile))
//      {
//
//         return false;
//
//      }
//
//      return estatus;

   }


   bool keyboard::load_os_layout(const ::file::path & path)
   {

      //int iCode;

      //int iScan;

      //::user::enum_key ekey;

      //::type typeinfoKey = ::type < ::user::enum_key >();

      string str = file()->as_string(scopedstrPath);

      informationf(scopedstrPath);

      informationf(str);

      if(str.is_empty())
      {
         informationf("unable to load os keyboard on_layout");
         //if(is_debugger_attached())
         //{

         //   Application.message_box(nullptr,"keyboard default.xml is empty?!?!?!?!");

         //}
         return false;
      }

      throw ::exception(todo, "xml");

      //::xml::document doc;

      //if(!doc.load(str))
      //{
      //   informationf("unable to load os keyboard on_layout");
      //   //if(is_debugger_attached())
      //   //{

      //   //   Application.message_box(nullptr,"keyboard default.xml syntax is incorrect?!?!?!?!");

      //   //}
      //   return false;
      //}

      //for(int i = 0; i < doc.root()->get_children_count(); i++)
      //{

      //   ::pointer<::xml::node>pnode = doc.root()->child_at(i);

      //   if(pnode->get_name().case_insensitive_order("item") == 0)
      //   {

      //      string strCode    = pnode->attribute("code");

      //      string strScan    = pnode->attribute("scan");

      //      string strExt    = pnode->attribute("ext");

      //      string strValue   = pnode->attribute("value");

      //      text_enum(ekey, strValue);

      //      if(strCode.has_character())
      //      {

      //         iCode    = atoi(strCode);

      //         m_mapKey.set_at(iCode,ekey);

      //      }

      //      if(strScan.has_character())
      //      {

      //         iScan    = atoi(strScan);

      //         if(strExt == "1")
      //         {

      //            m_mapExt.set_at(iScan,ekey);

      //         }
      //         else
      //         {

      //            m_mapScan.set_at(iScan,ekey);

      //         }

      //      }



      //   }

      //}

      //if((m_mapKey.get_count() + m_mapExt.get_count() + m_mapScan.get_count()) <= 0)
      //{

      //   if(is_debugger_attached())
      //   {

      //      Application.output_error_message("keyboard default.xml has no keyboard entries?!?!?!?!");

      //   }

      //}

      return true;

   }


   //class keyboard_layout & keyboard::on_layout()
   //{
   //
   //   return *m_playout;

   //}


   //void keyboard::process_escape(::pointer<::xml::node>pnode, ::property_set & set)
   //{
   //   m_playout->process_escape(pnode, set);
   //}

//   bool keyboard::load_layout(const_char_pointer pszPath, const ::action_context & context)
//   {
//
//      auto playout = __allocate ::user::keyboard_layout();
//
//      string strPath;
//      if(scopedstrPath == nullptr)
//      {
//         strPath = get_current_system_layout();
//      }
//      else
//      {
//         strPath = pszPath;
//      }
//      if(initialize(playout, strPath))
//      {
//         informationf("setting keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         if(playout->load(playout->m_strPath))
//         {
//            m_playout = playout;
//// xxx            Application.simpledb().on_set_keyboard_layout(playout->m_strPath, context);
//            informationf("successfully set keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//            return true;
//         }
//         else
//         {
//            playout->release();
//            informationf("failed to load keyboard on_layout : %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         }
//      }
//      else
//      {
//         informationf("failed to set keyboard on_layout path=%s", pszPath);
//      }
//      return false;
//   }

   //string keyboard::process_key(key * pkey)
   //{

   //   //if(m_playout == nullptr)
   //   //{

   //   //   return string((char)(pkey->m_nChar & 0xff));

   //   //}

   //   pkey->m_iCode = (int)(pkey->m_ekey);

   //   if(psession->is_key_pressed(::user::e_key_shift))
   //   {
   //      pkey->m_iCode |= I32_MINIMUM;
   //   }
   //   if(psession->is_key_pressed(::user::e_key_ralt))
   //   {
   //      pkey->m_iCode |= 0x40000000;
   //   }



   //   //return m_playout->process_key(pkey);

   //}

   //string keyboard::process_key(::user::enum_key ekey)
   //{

   //   if(m_playout == nullptr)
   //   {

   //      return string((char) ekey);

   //   }

   //   int iCode = (int) (ekey);

   //   if(psession->is_key_pressed(::user::e_key_shift))
   //   {
   //      iCode |= I32_MINIMUM;
   //   }
   //   if(psession->is_key_pressed(::user::e_key_ralt))
   //   {
   //      iCode |= 0x40000000;
   //   }

   //   return m_playout->process_key(iCode);

   //}

   //string keyboard::process_char(const_char_pointer pszKey)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszKey;
   //   }
   //   return m_playout->process_char(scopedstrKey);
   //}

   //string keyboard::process_escape(const_char_pointer pszEscape)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszEscape;
   //   }
   //   return m_playout->process_char(scopedstrEscape);
   //}


//   string keyboard::get_current_system_layout()
//   {
//
//      keyboard_layout_ida layoutida;
//
//      ::file::path_array patha;
//
//      Context.directory()->matter_ls_file("keyboard layout", patha);
//
//      for(int i = 0; i < patha.get_count(); i++)
//      {
//
//         keyboard_layout_id layoutid;
//
//         ::file::path path = patha[i];
//
//         if(initialize(&layoutid, path))
//         {
//
//            layoutida.add(layoutid);
//
//         }
//
//      }
//
//      ::sort::quick_sort(layoutida, true);
//
//#ifdef WINDOWS_DESKTOP
//
//
//      string strOverride = file_as_string(::dir::system() / "config\\system\\keyboard_layout.txt");
//
//      if(strOverride.has_character())
//      {
//
//         string strTest;
//
//         string strPath = Context.directory()->matter("keyboard layout/" + strOverride + ".xml");
//
//         strTest = Context.file()->as_string(strPath);
//
//         if(strTest.has_character())
//         {
//
//            return strPath;
//
//         }
//
//      }
//
//      wchar_t szLayoutName[KL_NAMELENGTH];
//
//      ::GetKeyboardLayoutNameW(szLayoutName);
//
//      HKL hkl = ::GetKeyboardLayout(0);
//
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_hkla.contains(hkl))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//      hkl = (HKL) (((uptr) hkl) & 0xffff);
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_hkla.contains(hkl))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#elif defined(LINUX) || defined(SOLARIS)
//
//      string strSymbol = x11_keyboard_get_current_group_symbol();
//
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_countrycode.case_insensitive_contains(strSymbol))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#elif defined(MACOS)
//
//      string strSymbol = keyboard_input_source();
//
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_keylayout.has_character() && strSymbol.contains(layoutida[i].m_keylayout))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#else
//
//      {
//
//         string strPath = Context.directory()->matter("keyboard layout/br_abnt2.xml");
//
//         if(Context.file()->exists(strPath))
//         {
//
//            return strPath;
//
//         }
//
//         return strPath;
//
//      }
//
//#endif
//
//      string strPath = Context.directory()->matter("keyboard layout/en_us_international.xml");
//
//      if(Context.file()->exists(strPath))
//      {
//
//         return strPath;
//
//      }
//
//      return "";
//
//   }


//   bool keyboard::initialize(keyboard_layout_id * playoutid, const_char_pointer pszPath)
//   {
//
//      if(!Context.file()->exists(scopedstrPath))
//         return false;
//
//      string str = Context.file()->as_string(scopedstrPath);
//
//      if(str.is_empty())
//         return false;
//
//      throw ::exception(todo("xml"));
//
////      ::xml::document doc;
////
////      if(!doc.load(str))
////         return false;
////
////      playoutid->m_strPath = pszPath;
////
////      playoutid->m_strName = doc.root()->attribute("name");
////
////      playoutid->m_countrycode = doc.root()->attribute("cc");
////
////      playoutid->m_keylayout = doc.root()->attribute("kl");
////
////      string_array straHkl;
////
////      straHkl.explode(";", doc.root()->attribute("hkla"));
////
////#ifdef WINDOWS_DESKTOP
////
////      for(int i = 0; i < straHkl.get_count(); i++)
////      {
////         string strHkl = straHkl[i];
////         HKL hkl;
////         strHkl.trim();
////         if(strHkl.case_insensitive_begins_eat("0x"))
////         {
////            hkl = (HKL) ::hex::to_uptr(strHkl);
////         }
////         else
////         {
////            hkl = (HKL) ansi_to_uptr(strHkl);
////         }
////         playoutid->m_hkla.add(hkl);
////      }
////
////#else
////
////      //throw ::exception(todo());
////
////#endif
////
////      if(playoutid->m_strName.is_empty())
////         return false;
//
//      return true;
//
//   }


   void keyboard::show_software_keyboard(::user::interaction_base* pprimitive, const ::scoped_string & scopedstr, character_count iBeg, character_count iEnd)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_iSoftwareKeyboardEventId++;

      ::collection::index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = pprimitive;

      fork([=,this]
           {

              sleep(400_ms);

              synchronous_lock synchronouslock(this->synchronization());

              if (iEventId == m_iSoftwareKeyboardEventId)
              {

                 ASSERT(pprimitive == m_pprimitiveSoftwareKeyboard);

                 synchronouslock.unlock();


                 throw 0;

                 //m_pprimitiveSoftwareKeyboard->show_software_keyboard(pprimitive, str, iBeg, iEnd);

              }

           });

      //return ::success;

   }


   void keyboard::hide_software_keyboard(::user::interaction_base * pprimitive)
   {

      if (!::is_null(pprimitive) && pprimitive != m_pprimitiveSoftwareKeyboard)
      {

         throw ::exception(error_bad_argument);

      }

      synchronous_lock synchronouslock(this->synchronization());

      m_iSoftwareKeyboardEventId++;

      ::collection::index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = nullptr;

      fork([this,iEventId,pprimitive]
           {

              sleep(400_ms);

              synchronous_lock synchronouslock(this->synchronization());

              if (iEventId == m_iSoftwareKeyboardEventId)
              {

                 synchronouslock.unlock();

                 m_pprimitiveSoftwareKeyboard->hide_software_keyboard(pprimitive);

              }

           });

      //return ::success;

   }


   void keyboard::translate_os_key_message(::user::key * pkey)
   {

      if(pkey->m_ekey == ::user::e_key_refer_to_text_member
         && pkey->m_strText.has_character())
      {

         return;

      }

      // auto ekey = ::x11::keysym_to_userkey(pkey->m_lparam);
      //
      // if(ekey != ::user::e_key_none)
      // {
      //
      //    pkey->m_ekey = ekey;
      //
      //    return;
      //
      // }
      //
      // if(pkey->m_ekey == ::user::e_key_none)
      // {
      //
      //    pkey->m_ekey = m_mapKey[(int) pkey->m_iVirtualKey];
      //
      // }

   }


//   void keyboard::__handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size)
//   {
////
////      if(format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
////      {
////
////         error() << "Only supported format is WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1";
////
////         return;
////
////      }
////
////      void * p = ::mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
////
////      if(p != MAP_FAILED)
////      {
////
////         error() << "wl_keyboard keymap mmap Failed";
////
////      }
////
////      synchronous_lock synchronouslock(this->synchronization());
////
//////      ::pointer < ::xkb_input::xkb_input > pxkbinput = system()->m_pinput;
//////
//////      if(pxkbinput)
//////      {
//////
//////         pxkbinput->xkb_keymap_new_from_string((const_char_pointer )p, XKB_KEYMAP_FORMAT_TEXT_V1,
//////                                             XKB_KEYMAP_COMPILE_NO_FLAGS);
//////
//////      }
////
////      m_pxkbkeymap = ::xkb_keymap_new_from_string(
////         m_pxkbcontext, (const_char_pointer )p, XKB_KEYMAP_FORMAT_TEXT_V1,
////         XKB_KEYMAP_COMPILE_NO_FLAGS);
////
////      ::munmap(p, size);
////
////      ::close(fd);
////
////      m_pxkbstate = ::xkb_state_new(m_pxkbkeymap);
////      if (!m_pxkbstate)
////      {
////         fprintf(stderr, "failed to create XKB state\n");
////         ::xkb_keymap_unref(m_pxkbkeymap);
////         m_pxkbkeymap = NULL;
////         return;
////      }
//
//   }


} // namespace windowing_q



