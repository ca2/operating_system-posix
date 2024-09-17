// Created by camilo on 2024-09-13 07:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/icon.h"
#include <gdk/gdk.h>

namespace innate_ui_gtk3
{


   class CLASS_DECL_INNATE_UI_GTK3 icon :
      virtual public ::innate_ui::icon
   {
   public:


      GdkPixbuf *  m_pgdkpixbuf;

      icon();
      ~icon() override;



   };


} // namespace innate_ui_gtk3



