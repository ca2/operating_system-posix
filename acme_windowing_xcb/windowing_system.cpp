//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"


namespace xcb
{


   windowing_system::windowing_system()
   {


   }


   windowing_system::~windowing_system()
   {


   }


   ::e_status windowing_system::defer_initialize_windowing_system()
   {

         return ::success;

   }


   ::e_status windowing_system::initialize_windowing_system()
   {

      informationf("node_gtk3::node::x11_initialize");

      informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");

      if (!system()->acme_windowing()->init_threads())
      {

         return ::error_failed;

      }


      return ::success;

   }



   void * windowing_system::get_display()
   {

      defer_initialize_windowing_system();

      return nullptr;

   }


   void windowing_system::sync(const ::procedure & procedure)
   {

      if(::is_main_thread())
      {

         procedure();

         return;

      }

      auto pevent = __allocate manual_reset_happening();

      user_post([ procedure, pevent ]
                {

                   procedure();

                   pevent->set_happening();

                });

      if(!pevent->wait(procedure.m_timeTimeout))
      {

         throw ::exception(error_timeout);

      }

   }


   void windowing_system::async(const ::procedure & procedure)
   {

      node()->user_post(procedure);

   }


   void windowing_system::display_error_trap_push(int i)
   {


   }


   void windowing_system::display_error_trap_pop_ignored(int i)
   {


   }


} // namespace xcb



