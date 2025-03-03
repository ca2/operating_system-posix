// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "innate_ui_q/dialog.h"
#include "window.h"


namespace innate_ui_q5
{


   class CLASS_DECL_INNATE_UI_Q5 dialog :
      virtual public ::innate_ui_q5::window,
      virtual public ::innate_ui_q::dialog
   {
   public:


      //GtkWidget *       m_pgtkwidgetFixed;


      dialog();
      ~dialog() override;


      // void create() override;
      // void _create() override;
      // //void _get_class(WNDCLASSEXW & wcex);
      // //void set_text(const ::scoped_string & scopedstr) override;
   };


} // namespace innate_ui_q5




