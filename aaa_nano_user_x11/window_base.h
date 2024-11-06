//
// Created by camilo on 2024-10-03 04:23 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "nano_user_x11/event_listener.h"
#include "nano_user_x11/window_base_handle.h"
#include "acme/windowing/window_base.h"


namespace x11
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_NANO_USER_X11 window_base :
            virtual public ::acme::windowing::window,
            virtual public ::x11::micro::window_base_handle,
            virtual public ::x11::event_listener
         {
         public:


            window_base();
            ~window_base() override;


            void set_rectangle_unlocked(const ::int_rectangle & rectangle) override;
            void set_position_unlocked(const ::int_point & point) override;
            void set_size_unlocked(const ::int_size & size) override;

            ::int_rectangle get_window_rectangle_unlocked() override;

            virtual void _defer_translate_to_absolute_coordinates_unlocked(::int_point & point);


         };


      } // user


   } // nano


} // x11




