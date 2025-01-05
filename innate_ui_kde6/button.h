// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/button.h"
#include "window.h"
//#include <gtk/gtk.h>

namespace innate_ui_kde5
{


   class CLASS_DECL_INNATE_UI_GTK3 button :
    virtual public ::innate_ui_kde5::window,
      virtual public ::innate_ui::button
   {
   public:


     //GtkWidget * m_pgtkwidget;

      button();
      ~button() override;


      void _create_child(window * pwindowParent) override;

      //bool _on_command() override;

      void set_icon(::innate_ui::icon * picon) override;
      void set_callback_on_click(const ::procedure & callbackOnClick) override;
      void set_text(const ::scoped_string & scopedstr) override;

   };


} // namespace innate_ui_win32




