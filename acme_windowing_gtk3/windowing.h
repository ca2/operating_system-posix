//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"


namespace gtk3
{


   namespace acme
   {


      namespace windowing
      {


	
      class CLASS_DECL_ACME_WINDOWING_GTK3 windowing :
           virtual public ::acme::windowing::windowing
   {
   public:

      ::procedure             m_callbackOnActivateGtkApplication;
      GtkApplication *        m_pgtkapplication;


      windowing();
      ~windowing() override;



      void on_start_system() override;

      //::e_status defer_initialize_windowing_system() override;
      void initialize_windowing() override;

      void windowing_application_main_loop() override;
      void windowing_post_quit() override;
      virtual void _on_activate_gtk_application();




      ::acme::windowing::display * acme_display() override;
      void _user_send(const ::procedure & procedure) override;
      void _user_post(const ::procedure & procedure) override;
      //void display_error_trap_push(int i) override;
      //void display_error_trap_pop_ignored(int i) override;

//   ::e_status x11_initialize() override;
//   void * x11_get_display() override;
//   void x11_sync(const ::procedure & procedure) override;
//   void x11_async(const ::procedure & procedure) override;
//   void x11_display_error_trap_push(int i) override;
//   void x11_display_error_trap_pop_ignored(int i) override;

      //void main_post(const ::procedure & procedure) override;


      ::pixmap get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


   };

      
      } // namespace windowing


   } // namespace acme


} // namespace gtk3



