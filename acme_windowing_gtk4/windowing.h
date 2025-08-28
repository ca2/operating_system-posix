//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/prototype/collection/list.h"

#include <gtk/gtk.h>


namespace gtk4
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_GTK4 windowing :
            virtual public ::acme::windowing::windowing,
            virtual public ::task_handler
         {
         public:


            ::pointer < manual_reset_happening >    m_phappeningCreatingWGtk4Display;


            ::procedure                         m_callbackOnActivateGtkApplication;
            GtkApplication *                    m_pgtkapplication;
            gpointer                            m_pGtkSettingsDefault;

            GAction *                           m_pactionColorScheme = nullptr;


            itask                               m_itask;

            ::procedure_list_base               m_procedurelist;
            ::procedure_list_base               m_procedurelistPriority;


            windowing();
            ~windowing() override;


            void process_messages() override;


            void on_start_system() override;


            //void defer_initialize_windowing() override;


            void initialize_windowing() override;


            void destroy() override;


            //void* get_display() override;


            ::color::color get_operating_system_background_color() override;


            void _user_post(const ::procedure& procedure) override;

            void _user_send(const ::procedure& procedure) override;

            void _main_send(const ::procedure& procedure) override;


            void _main_post(const ::procedure& procedure) override;




            //void _post(const ::procedure& procedure) override;


            void display_error_trap_push(int i) override;


            void display_error_trap_pop_ignored(int i) override;


            //   ::e_status x11_initialize() override;
            //   void * x11_get_display() override;
            //   void x11_sync(const ::procedure & procedure) override;
            //   void x11_async(const ::procedure & procedure) override;
            //   void x11_display_error_trap_push(int i) override;
            //   void x11_display_error_trap_pop_ignored(int i) override;
            bool is_branch_current() const override;


            void windowing_application_main_loop() override;


            void run() override;


            void __task_suffix() override;


            bool handle_messages() override;


            void windowing_post_quit() override;


            virtual void _on_activate_gtk_application();


            virtual void _hook_system_theme_change_callbacks();


            void fetch_dark_mode() override;


            virtual ::string _get_os_user_theme();


            virtual ::string _get_os_user_icon_theme();


            virtual void _on_os_user_theme_change();


            virtual void _on_os_user_icon_theme_change();


            virtual void _on_color_scheme_change();


            // virtual void _apply_os_user_theme();
            // virtual void _os_process_user_theme(const ::scoped_string & scopedstrOsUserTheme);
            // //virtual ::string _get_os_user_theme();
            //
            //
            // virtual void _apply_os_user_icon_theme();
            // virtual void _os_process_user_icon_theme(const ::scoped_string & scopedstrOsUserIconTheme);

            ::pixmap get_pixmap_from_file(memory& memoryHost, const void* psourceFile, memsize sizeSourceFile) override;


            //svirtual ::acme::windowing::display * _defer_get_display(bool bBranch, ::GdkDisplay * pgdkdisplay);


            ::windowing::enum_windowing calculate_ewindowing() override;


            bool has_resizing() override;


            void set_dark_mode(bool bDarkMode) override;
            bool dark_mode() override;

         };


      } // namespace windowing


   } // namespace


} // namespace windowing_system_gtk4
