//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#pragma once


//#include "_.h"
//#include "windowing_system_wayland/xkb_input.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size_array.h"
#include "acme/windowing/display.h"

#include <gtk/gtk.h>



//#include "display_base.h"
//#include "event_listener.h"
//#include "windowing_system_x11/_atom.h"


//struct wl_display;


namespace g
{


   namespace acme
   {


      namespace windowing
      {


         class window;


         class CLASS_DECL_ACME_WINDOWING_G display :
            virtual public ::acme::windowing::display
         {
         public:


            display();
            ~display() override;


            void initialize(::particle * pparticle) override;


            ::string _get_wallpaper(::collection::index iMonitorIndex) override;
            void _set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper) override;
            void enable_wallpaper_change_notification() override;

            bool is_x11() override;


            bool is_wayland() override;


            virtual void _on_wallpaper_change();


         };


      } //namespace windowing


   } // namespace acme


} // namespace g



