// Created by camilo on 2024-09-13 01:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/innate_ui.h"
//#include <gtk/gtk.h>


namespace innate_ui_motif
{

   class window;

   class CLASS_DECL_INNATE_UI_MOTIF innate_ui :
      virtual public ::innate_ui::innate_ui
   {
   public:


      bool m_bRunning;


      map_base < Widget, ::pointer < window > >     m_windowmap;
      //string_map_base < ATOM >                    m_classmap;
      bool m_bXtAppInitialized = false;
      XtAppContext m_xtappcontext;


      innate_ui();
      ~innate_ui() override;

      void on_initialize_particle() override;
      
      //void _defer_run_innate_ui_gtk2_user_loop();

      virtual void _defer_xt_app_initialize();
      virtual void _xt_app_initialize();
      virtual void _xt_app_do_happenings();
      
      void _user_post(const ::procedure & procedure) override;


      //virtual LRESULT _window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

      //virtual void _defer_show_system_menu(HWND hwnd, const ::int_point & pointAbsolute);


   };

   //LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

} // namespace innate_ui



