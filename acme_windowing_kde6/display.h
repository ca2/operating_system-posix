//
// From acme_windowing_gkt3/display on 2025-01-10 01:18 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_q6/display.h"


namespace kde6
{


   namespace acme
   {


      namespace windowing
      {


         class window;

         using window_map = map_base<::QWidget *, ::pointer<window> >;

         class CLASS_DECL_ACME_WINDOWING_KDE6 display :
            virtual public ::q6::acme::windowing::display
         {
         public:




            display();
            ~display() override;

            void  enable_wallpaper_change_notification() override;
            void _set_wallpaper(::collection::index i, const ::scoped_string & strLocalImagePath) override;
            ::string _get_wallpaper(::collection::index i) override;


         };


         //CLASS_DECL_NANO_USER_X11 display * display_get(::particle * pparticle, bool bBranch = true, Display * pdisplay = nullptr);


      } // namespace windowing


   } // namespace acme


} // namespace kde6



