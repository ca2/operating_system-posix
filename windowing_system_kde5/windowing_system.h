//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing_base.h"
#include <QApplication>


namespace windowing_system_kde5
{


   class CLASS_DECL_WINDOWING_SYSTEM_KDE5 windowing_system :
           virtual public ::windowing::windowing_base
   {
   public:


      QApplication * m_pqapplication;


      windowing_system();
      ~windowing_system() override;

      ::e_status defer_initialize_windowing_system() override;
      ::e_status initialize_windowing_system() override;
      void * get_display() override;
      void sync(const ::procedure & procedure) override;
      void async(const ::procedure & procedure) override;
      void display_error_trap_push(int i) override;
      void display_error_trap_pop_ignored(int i) override;


      void user_post(const ::procedure & procedureParam) override;


      virtual void _on_activate_kde_application();


      void on_start_system() override;


      void windowing_system_application_main_loop() override;
      void windowing_system_post_quit() override;


      virtual ::pixmap get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


//   ::e_status x11_initialize() override;
//   void * x11_get_display() override;
//   void x11_sync(const ::procedure & procedure) override;
//   void x11_async(const ::procedure & procedure) override;
//   void x11_display_error_trap_push(int i) override;
//   void x11_display_error_trap_pop_ignored(int i) override;


   };



} // namespace windowing_system_kde5



