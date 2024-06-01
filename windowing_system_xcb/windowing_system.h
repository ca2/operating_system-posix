//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing_system/windowing_system.h"


namespace xcb
{


   class CLASS_DECL_WINDOWING_SYSTEM_XCB windowing_system :
           virtual public ::windowing_system::windowing_system
   {
   public:



      windowing_system();
      ~windowing_system() override;


      ::e_status defer_initialize_windowing_system() override;
      ::e_status initialize_windowing_system() override;
      void * get_display() override;
      void sync(const ::procedure & procedure) override;
      void async(const ::procedure & procedure) override;
      void display_error_trap_push(int i) override;
      void display_error_trap_pop_ignored(int i) override;


   };



} // namespace xcb



