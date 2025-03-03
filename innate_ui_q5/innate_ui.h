// Created by camilo on 2024-09-13 01:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "innate_ui_q/innate_ui.h"
//#include <gtk/gtk.h>


namespace innate_ui_q5
{

   class window;

   class CLASS_DECL_INNATE_UI_Q5 innate_ui :
      virtual public ::innate_ui_q::innate_ui
   {
   public:


      // bool m_bRunning;
      //
      //
      // map < QWidget *, ::pointer < window > >     m_windowmap;
      // //string_map < ATOM >                    m_classmap;

      innate_ui();
      ~innate_ui() override;

      // void on_initialize_particle() override;
      //
      // //void _defer_run_innate_ui_gtk2_user_loop();
      //
      // //void post(const ::procedure & procedure) override;
      // //void sync(const ::procedure & procedure) override;
      //
      //
      // //virtual LRESULT _window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
      //
      // //virtual void _defer_show_system_menu(HWND hwnd, const ::int_point & pointAbsolute);
      // //::pointer < ::innate_ui::icon > innate_ui_icon(const ::payload & payloadFile, const ::int_size & size) override;

   };

   //LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

} // namespace innate_ui



