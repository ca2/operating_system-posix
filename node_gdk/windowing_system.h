//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing_system/windowing_system.h"


namespace x11
{


    class CLASS_DECL_WINDOWING_SYSTEM_X11 windowing_system :
        virtual public ::windowing_system::windowing_system
    {
    public:


        void *                                                m_pvoidX11Display;
        ::e_status                                            m_estatusInitializeX11;


       windowing_system();
       ~windowing_system() override;

        ::e_status defer_initialize_windowing_system() override;
        ::e_status initialize_windowing_system() override;
        void * get_display() override;
        void sync(const ::procedure & procedure) override;
        void async(const ::procedure & procedure) override;
        void display_error_trap_push(int i) override;
        void display_error_trap_pop_ignored(int i) override;

//   ::e_status x11_initialize() override;
//   void * x11_get_display() override;
//   void x11_sync(const ::procedure & procedure) override;
//   void x11_async(const ::procedure & procedure) override;
//   void x11_display_error_trap_push(int i) override;
//   void x11_display_error_trap_pop_ignored(int i) override;


};



} // namespace x11



