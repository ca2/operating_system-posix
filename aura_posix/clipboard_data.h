//
// Created by camilo on 20/01/2021.
//
#pragma once


#include "aura/graphics/image/image.h"
#include "aura/user/user/copydesk.h"


enum enum_clipboard
{

   e_clipboard_none,
   e_clipboard_error,
   e_clipboard_get_plain_text,
   e_clipboard_set_patha,
   e_clipboard_get_patha,
   e_clipboard_get_file_target_count,
   e_clipboard_get_image,

};


struct clipboard_data :
   virtual public ::object
{
public:


   ::user::copydesk::enum_op     m_eop;
   enum_clipboard                m_eclipboard;
   manual_reset_event            m_event;
   string                        m_str;
   ::image_pointer               m_pimage;
   ::file::path_array                 m_patha;
   int                           m_nTargets;


   clipboard_data(::particle * pparticle, enum_clipboard eclipboard)
   {

      initialize(pparticle);

      m_eclipboard = eclipboard;

      m_event.ResetEvent();

   }



};



