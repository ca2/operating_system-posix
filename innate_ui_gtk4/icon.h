// Created by camilo on 2024-09-13 07:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/icon.h"
#include <gtk/gtk.h>

namespace innate_ui_gtk4
{


   class CLASS_DECL_INNATE_UI_GTK3 icon :
      virtual public ::innate_ui::icon
   {
   public:


      GdkPaintable *  m_pgdkpaintable;

      icon();
      ~icon() override;


      void _create() override;


   };


} // namespace innate_ui_gtk4



