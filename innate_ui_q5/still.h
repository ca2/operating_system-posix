// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "innate_ui_q/still.h"
#include "window.h"
//#include <gtk/gtk.h>

namespace innate_ui_q5
{


   class CLASS_DECL_INNATE_UI_Q5 still :
      virtual public ::innate_ui_q5::window,
      virtual public ::innate_ui_q::still
   {
   public:

      //GtkWidget * m_pgtkwidget;

      //bool m_bIcon;

      still();
      ~still() override;


      // void _create_child(window * pwindowParent) override;
      // void create_icon_still(::innate_ui::window * pwindowParent) override;
      //
      // void set_icon(::innate_ui::icon * picon) override;
      // void set_text(const ::scoped_string & scopedstr) override;
   };


} // namespace innate_ui_q5




