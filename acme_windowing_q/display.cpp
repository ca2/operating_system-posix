//
// From acme_windowing_gkt3/display on 2025-01-10 01:20 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/constant/windowing2.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include <QScreen>
#include <QRect>
#include <QGuiApplication>


#ifdef OPENBSD

#include <stdio.h>

#endif



void set_main_user_thread();


namespace q
{


   namespace acme
   {


      namespace windowing
      {


         display::display()
         {

            m_bUnhook = false;


            defer_create_synchronization();


         }


         display::~display()
         {


         }


         void display::open_display()
         {

            if (m_bQDisplayOpened)
            {

               return;

            }

            m_bQDisplayOpened = true;

            ::acme::windowing::display::open_display();

         }


         bool display::is_display_opened() const
         {

            return m_bQDisplayOpened;


         }



         bool display::message_loop_step()
         {


            return true;

         }

         void display::message_loop()
         {

            bool bHandled1;

            bool bHandled2;

            information() << "x11::acme::windowing::display::message_loop";

            while (::task_get_run()) {

               if (m_bUnhook) {

                  break;

               }

               bHandled1 = false;

               bHandled2 = false;

               while (message_loop_step()) {

                  bHandled1 = true;

               }

               //               if(!bHandled1)
               //               {
               //
               //                  bHandled2 = x11_posted();
               //
               //               }

               if (!bHandled1 && !bHandled2) {

                  preempt(5_ms);

               }

            }

            information() << "Finished display::message_loop for nano::display";

         }


         void display::init_task()
         {

            informationf("x11 nano display init_task");

         }


         bool display::is_branch_current() const
         {

            if (!m_bUnhook && ::object::is_branch_current()) {

               return true;

            }

            if (m_bUnhook && ::is_main_thread()) {

               return true;

            }

            return false;

         }


         void display::run()
         {

            ::task_set_name("x11:display:run");

            information() << "x11::display::run";

            message_loop();

         }


         ::int_size display::get_main_screen_size()
         {


            QScreen *primaryScreen = QGuiApplication::primaryScreen();
            if (!primaryScreen) {
              // qWarning() << "No primary screen found!";
               return {1920,1080};
            }

            // Get the screen geometry
            QRect screenGeometry = primaryScreen->geometry();
            int width = screenGeometry.width();
            int height = screenGeometry.height();

            //qDebug() << "Primary screen size: " << width << "x" << height;

            return {width, height};

         }



         bool display::is_dark_mode_through_theming()
         {

            auto edesktop = ::windowing::get_eoperating_ambient();

            switch (edesktop) {
               case ::windowing::e_operating_ambient_gnome:
                  return false;
               case ::windowing::e_operating_ambient_mate:
                  return false; // don't know yet
               case ::windowing::e_operating_ambient_lxde:
                  return false; // don't know yet
               case ::windowing::e_operating_ambient_xfce:
                  return true;
               case ::windowing::e_operating_ambient_kde:
                  return true;
               default:
                  return false;
            }
         }


         string display::theming_ui_name()
         {

            auto edesktop = ::windowing::get_eoperating_ambient();

            switch (edesktop) {
               case ::windowing::e_operating_ambient_kde:
                  return "KDE Plasma Global Theme";
               default:
                  return ::acme::windowing::display::theming_ui_name();
            };

         }


         void display::impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme)
         {


         }


         void display::_set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper)
         {

         }


         ::string display::impl_get_desktop_theme()
         {

            return {};

         }


         void display::set_desktop_icon_theme(const ::scoped_string & scopedtrDesktopIconTheme)
         {


         }


      } // namespace windowing


   } // namespace acme


} // namespace q



