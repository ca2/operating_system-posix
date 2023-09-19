//
// Created by camilo on 9/18/23 16:11 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace xinput
{


   class xinput
   {
   public:



      ::string       m_strXkbKeymapString;
      ::i32          m_iXkbKeymapFormat;
      ::i32          m_iXkbKeymapFlags;
      bool           m_bNewXkbKeymap;


      virtual bool __handle_xinput(void * p, void * cookie) = 0;
      virtual void __xkb_keymap_new_from_string2(const char * p, int format, int flags) = 0;



      virtual void xkb_keymap_new_from_string(const char * p, int format, int flags);


      virtual void defer_update_xkb_keymap();


   };


} // namespace xinput



