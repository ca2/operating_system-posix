//
// From acme_windowing_gkt3/display on 2025-01-10 01:18 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/display.h"
#include <QWidget>


namespace q
{


   namespace acme
   {


      namespace windowing
      {


         class window;

         using window_map = map_base<::QWidget *, ::pointer<window> >;

         class CLASS_DECL_COMMON_Q display :
            virtual public ::acme::windowing::display
         {
         public:


            bool                                         m_bUnhook;
            window_map                                   m_windowmap;

            bool                                         m_bQDisplayOpened;


            display();
            ~display() override;


            bool is_branch_current() const override;


            void open_display() override;

            bool is_display_opened() const override;


            bool message_loop_step();
            void message_loop();

            void init_task() override;

            void run() override;


            ::int_size get_main_screen_size() override;


            bool is_dark_mode_through_theming() override;

            ::string theming_ui_name() override;


            void _set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper) override;


            void impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme) override;

            ::string impl_get_desktop_theme() override;


            void set_desktop_icon_theme(const ::scoped_string & scopedtrDesktopIconTheme) override;


         };



      } // namespace windowing


   } // namespace acme


} // namespace q



