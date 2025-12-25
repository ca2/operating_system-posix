// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/dialog.h"
#include "window.h"


namespace innate_ui_xaw
{


   class CLASS_DECL_INNATE_UI_XAW dialog :
      virtual public ::innate_ui_xaw::window,
      virtual public ::innate_ui::dialog
   {
   public:


      GtkWidget *m_fixed;
      dialog();
      ~dialog() override;

void create() override;
      void _create() override;
      //void _get_class(WNDCLASSEXW & wcex);
      //void set_text(const ::scoped_string & scopedstr) override;
   };


} // namespace innate_ui_xaw




