//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"


namespace x11
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_X11 windowing :
                 virtual public ::acme::windowing::windowing
         {
         public:


            //void *                                                m_p_Display;
            ::e_status                                            m_estatusInitializeX11;


            windowing();
            ~windowing() override;

            //::e_status defer_initialize_windowing() override;
            //::e_status initialize_windowing() override;
            void initialize_windowing() override;
            //virtual void * get_Display();
            void _main_send(const ::procedure & procedure) override;
            void _main_post(const ::procedure & procedure) override;
            void display_error_trap_push(int i) override;
            void display_error_trap_pop_ignored(int i) override;

            //   ::e_status x11_initialize() override;
            //   void * x11_get_display() override;
            //   void x11_sync(const ::procedure & procedure) override;
            //   void x11_async(const ::procedure & procedure) override;
            //   void x11_display_error_trap_push(int i) override;
            //   void x11_display_error_trap_pop_ignored(int i) override;


         };


      } // namespace windowing


   } // namespace acme


} // namespace x11



