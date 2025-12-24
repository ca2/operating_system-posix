// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-05-22 03:05 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "aura/windowing/windowing.h"


namespace windowing_posix
{


   class CLASS_DECL_AURA_POSIX windowing :
      virtual public ::windowing::windowing
   {
   public:


      void *                                          m_pSnLauncheeContext;


      windowing();
      ~windowing() override;


      void _libsn_start_context() override;


      //void _defer_position_and_size_message(oswindow oswindow);
      virtual void _configure_message(::windowing::window * pwindow, const ::int_rectangle & rectangle);
      //virtual void _size_message(::windowing::window * pwindow, const ::int_size & size);


//      virtual void _on_wm_state_change(::windowing::window * pxwindow);

      //virtual ::pointer <::input::input> _get_input();


   };



} // namespace windowing_posix



