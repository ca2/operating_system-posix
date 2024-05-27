//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"


namespace x11
{


    windowing_system::windowing_system()
    {

        m_pvoidX11Display = nullptr;
        m_estatusInitializeX11 = e_status_not_initialized;

    }


    windowing_system::~windowing_system()
    {


    }


    void node::sync(const ::procedure & procedure)
    {

        nano()->user()->x11_sync(procedure);

    }


    void node::async(const ::procedure & procedure)
    {

        nano()->user()->x11_async(procedure);

    }


    void node::display_error_trap_push(int i)
    {


    }


    void node::display_error_trap_pop_ignored(int i)
    {


    }


} // namespace windowing_system



