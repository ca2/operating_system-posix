// Created by camilo on 2024-09-13 07:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/icon.h"
//#include "app-graphics3d/draw2d_vulkan/bitmap.h"
//#include <gdk/gdk.h>
// #include <X11/Xaw/Command.h>
// #include <X11/Intrinsic.h>
// #include <X11/Xutil.h>


namespace innate_ui_xaw
{


   class CLASS_DECL_INNATE_UI_XAW icon :
      virtual public ::innate_ui::icon
   {
   public:


      Pixmap         m_pixmap;
      XImage *       m_pimage;
//      GdkPixbuf *  m_pgdkpixbuf;

      icon();
      ~icon() override;

      void _create() override;


   };


} // namespace innate_ui_xaw



