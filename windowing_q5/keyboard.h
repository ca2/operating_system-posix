//
// Created by camilo on 15/02/2021. 22:01 BRT <3TBS_!!
//// from aura/user/keyboard
////
//
#pragma once


#include "windowing_q/keyboard.h"
//#include "windowing_system_wayland/xkb_input.h"


namespace windowing_q5
{

   //class keyboard_layout;

   class CLASS_DECL_WINDOWING_Q5 keyboard :
      virtual public ::windowing_q::keyboard
      //,
      //virtual public ::xkb_input::xkb_input
   {
      public:
      //
      //
      // ::pointer<::user::interaction_base>             m_pprimitiveSoftwareKeyboard;
      // ::collection::index                                     m_iSoftwareKeyboardEventId;
      //
      //
      // ::int_map < ::user::enum_key >              m_mapExt;
      // ::int_map < ::user::enum_key >              m_mapScan;
      // ::int_map < ::user::enum_key >              m_mapKey;
      // //::pointer<keyboard_layout>                   m_playout;
      // //::xkb_keymap *                            m_pxkbkeymap;
      // //::xkb_context *                           m_pxkbcontext;
      // //::xkb_state *                             m_pxkbstate;


      keyboard();
      ~keyboard() override;

      //
      // virtual void enum_init(::platform::system * psystem);
      //
      // //virtual class keyboard_layout & on_layout();
      //
      // void initialize(::particle * pparticle) override;
      //
      // //bool load_layout(const char * pszPath, const ::action_context & action_context);
      //
      // //string process_key(key * pkey);
      //
      // //string process_key(::user::enum_key ekey);
      //
      // //string process_char(const char * pszChar);
      //
      // //string process_escape(const char * pszChar);
      //
      // //void process_escape(::pointer<::xml::node>pnode, property_set & set);
      //
      // //string get_current_system_layout();
      //
      // //bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);
      //
      // void translate_os_key_message(::user::key * pkey) override;
      //
      // bool load_os_layout(const ::file::path & pszPath) override;
      //
      // void show_software_keyboard(::user::interaction_base * pprimitive, string str, character_count iBeg, character_count iEnd);
      //
      // void hide_software_keyboard(::user::interaction_base * pprimitive);
      //
      //
      // //virtual void __handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);
      //

   };


} // namespace windowing_q5
