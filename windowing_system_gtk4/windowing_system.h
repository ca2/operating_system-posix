//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing_base.h"
#include "acme/prototype/collection/list.h"

#include <gtk/gtk.h>


namespace windowing_system_gtk4
{


   class CLASS_DECL_WINDOWING_SYSTEM_GTK4 windowing_system :
           virtual public ::windowing::windowing_base
   {
   public:


      ::procedure          m_callbackOnActivateGtkApplication;
      GtkApplication *     m_pgtkapplication;
      gpointer             m_pGtkSettingsDefault;

      GAction *m_pactionColorScheme = nullptr;


      itask_t              m_itask;

      ::procedure_list     m_procedurelist;
      ::procedure_list     m_procedurelistPriority;

      windowing_system();
      ~windowing_system() override;

      void process_messages() override;

      void on_start_system() override;

      ::e_status defer_initialize_windowing_system() override;
      ::e_status initialize_windowing_system() override;
      void * get_display() override;
      void sync(const ::procedure & procedure) override;


      void main_post(const ::procedure & procedure) override;
      void async(const ::procedure & procedure) override;


      void display_error_trap_push(int i) override;
      void display_error_trap_pop_ignored(int i) override;

//   ::e_status x11_initialize() override;
//   void * x11_get_display() override;
//   void x11_sync(const ::procedure & procedure) override;
//   void x11_async(const ::procedure & procedure) override;
//   void x11_display_error_trap_push(int i) override;
//   void x11_display_error_trap_pop_ignored(int i) override;
      bool is_branch_current() const override;
      void windowing_system_application_main_loop() override;
      void windowing_system_post_quit() override;
      virtual void _on_activate_gtk_application();

      virtual void _hook_system_theme_change_callbacks();

      virtual void _fetch_dark_mode();


      virtual ::string _get_os_user_theme();
      virtual ::string _get_os_user_icon_theme();

      virtual void _on_os_user_theme_change();
      virtual void _on_os_user_icon_theme_change();


      virtual void _on_color_scheme_change();

      // virtual void _apply_os_user_theme();
      // virtual void _os_process_user_theme(string strOsUserTheme);
      // //virtual ::string _get_os_user_theme();
      //
      //
      // virtual void _apply_os_user_icon_theme();
      // virtual void _os_process_user_icon_theme(string strOsUserIconTheme);

      ::pixmap get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile) override;





   };



} // namespace windowing_system_gtk4



