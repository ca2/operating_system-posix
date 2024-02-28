//
// Created by camilo on 15/02/2021. 22:01 BRT <3TBS_!!
//// from aura/user/keyboard
////
//
#pragma once


#include "aura/windowing/keyboard.h"


namespace windowing_xcb
{

   //class keyboard_layout;

   class CLASS_DECL_WINDOWING_XCB keyboard :
      virtual public ::windowing::keyboard
   {
   public:


      ::pointer<::user::primitive>             m_pprimitiveSoftwareKeyboard;
      index                                     m_iSoftwareKeyboardEventId;


      ::i32_map < ::user::enum_key >              m_mapExt;
      ::i32_map < ::user::enum_key >              m_mapScan;
      ::i32_map < ::user::enum_key >              m_mapKey;
      //::pointer<keyboard_layout>                   m_playout;

      keyboard();
      ~keyboard() override;

      //virtual class keyboard_layout & on_layout();

      void initialize(::particle * pparticle) override;

      //bool load_layout(const char * pszPath, const ::action_context & action_context);

      //string process_key(key * pkey);

      //string process_key(::user::enum_key ekey);

      //string process_char(const char * pszChar);

      //string process_escape(const char * pszChar);

      //void process_escape(::pointer<::xml::node>pnode, property_set & set);

      //string get_current_system_layout();

      //bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

      virtual void translate_os_key_message(::user::key * pkey) override;

      virtual bool load_os_layout(const ::file::path & pszPath) override;

      //void show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd) override;

      //void hide_software_keyboard(::user::primitive * pprimitive) override;


   };


} // namespace user
