//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#pragma once


#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/collection/array_base.h"
#include "acme/windowing/display.h"

#include <X11/Xlib.h>



namespace x11
{


   namespace acme
   {


      namespace windowing
      {


         class window;


         class CLASS_DECL_ACME_WINDOWING_X11 display :
            virtual public ::acme::windowing::display
         {
         public:


            bool m_bOpened;
            Display* m_pDisplay;
            Window m_windowRoot;

            bool m_bOwnDisplay;

            bool m_bMouseCaptured;
            ::int_rectangle m_rectangleMouseCapture;
            ::int_rectangle_array m_rectangleaMonitor;

            bool                                      m_bUnhook;


            display();
            ~display() override;


            void initialize(::particle * pparticle) override;


            virtual void set_x11_display(::Display * pgdkdisplay);


            bool is_branch_current() const override;


            void open_display() override;


            bool is_wallpaper_associated_with_dark_mode() override;



            ::int_size get_main_screen_size() override;


            virtual ::Display* __get_x11_display();

            virtual ::Window __get_x11_root_window();


            virtual void open();


            virtual void close();


            void destroy() override;



            virtual ::Display* _x11_display();


            virtual ::Display* _x11_display() const;


            virtual Window _x11_focus();


            void display_post(const procedure& procedure) override;



            bool is_x11() override;


            bool is_wayland() override;


         };


      } //namespace windowing


   } // namespace acme


} // namespace x11



