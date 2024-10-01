//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing_system/windowing_system.h"


namespace windowing_system_gtk3
{


   class CLASS_DECL_WINDOWING_SYSTEM_GTK3 windowing_system :
           virtual public ::windowing_system::windowing_system
   {
   public:

      ::procedure             m_callbackOnActivateGtkApplication;
      GtkApplication *        m_pgtkapplication;


      windowing_system();
      ~windowing_system() override;



      void on_start_system() override;

      ::e_status defer_initialize_windowing_system() override;
      ::e_status initialize_windowing_system() override;

      void windowing_system_application_main_loop() override;
      void windowing_system_post_quit() override;
      virtual void _on_activate_gtk_application();




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

      void main_post(const ::procedure & procedure) override;


      ::pixmap get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


   };



} // namespace windowing_system_gtk3



