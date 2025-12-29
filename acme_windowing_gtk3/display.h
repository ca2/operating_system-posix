//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_g/display.h"
//#include "event_listener.h"
//#include "windowing_system_x11/_atom.h"


namespace gtk3
{


   namespace acme
   {


      namespace windowing
      {


         class window;

         using window_map = map_base<::GtkWidget *, ::pointer<window> >;

         class CLASS_DECL_ACME_WINDOWING_GTK3 display :
            virtual public ::g::acme::windowing::display //,     virtual public event_listener
         {
         public:


            bool                                         m_bUnhook;

            window_map                                   m_windowmap;


            display();
            ~display() override;


            bool is_branch_current() const override;




            bool message_loop_step();
            void message_loop();

            void init_task() override;

            void run() override;


            ::int_size get_main_screen_size() override;


            virtual void _gtk3_release_mouse_capture();

            bool is_dark_mode_through_theming() override;

            ::string theming_ui_name() override;


            //void _set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper) override;


            void impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme) override;

            ::string impl_get_desktop_theme() override;


            void set_desktop_icon_theme(const ::scoped_string & scopedtrDesktopIconTheme) override;


         };


         //CLASS_DECL_NANO_USER_X11 display * display_get(::particle * pparticle, bool bBranch = true, Display * pdisplay = nullptr);


      } // namespace windowing


   } // namespace acme


} // namespace gtk3



