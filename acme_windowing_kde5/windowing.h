//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include <QApplication>


namespace kde5
{


   namespace acme
   {


      namespace windowing
      {


   class CLASS_DECL_ACME_WINDOWING_KDE5 windowing :
           virtual public ::acme::windowing::windowing
   {
   public:


      QApplication * m_pqapplication;


      windowing();
      ~windowing() override;

      //::e_status defer_initialize_windowing() override;
      void initialize_windowing() override;
      ::acme::windowing::display * acme_display() override;
      void _main_send(const ::procedure & procedure) override;
      void _main_post(const ::procedure & procedure) override;
      void _user_send(const ::procedure & procedure) override;
      void _user_post(const ::procedure & procedure) override;

      void display_error_trap_push(int i) override;
      void display_error_trap_pop_ignored(int i) override;


      //void user_post(const ::procedure & procedureParam) override;


      virtual void _on_activate_kde_application();


      void on_start_system() override;


      void windowing_application_main_loop() override;
      void windowing_post_quit() override;


      bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);


      virtual ::pixmap get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


//   ::e_status x11_initialize() override;
//   void * x11_get_display() override;
//   void x11_sync(const ::procedure & procedure) override;
//   void x11_async(const ::procedure & procedure) override;
//   void x11_display_error_trap_push(int i) override;
//   void x11_display_error_trap_pop_ignored(int i) override;


   };


      } //namespace windowing


   } //namespace acme


} // namespace kde5



