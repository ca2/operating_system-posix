//
// Created by camilo on 4/2/26.
//
//
// Created by camilo on 2024-04-02 01:39 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "windowing.h"

#include "acme/constant/windowing2.h"
#include "acme/handler/request.h"
#include "acme/platform/application.h"
#include  "acme/operating_system/posix/termination_handler.h"
#include <glib-unix.h>

namespace g
{


   namespace acme
   {


      namespace windowing
      {


         windowing::windowing()
         {


         }


         windowing::~windowing()
         {


         }


         ::string windowing::get_version()
         {

            ::string str;

            str.format("{}.{}.{}",
               gtk_get_major_version(),
               gtk_get_minor_version(),
               gtk_get_micro_version());

            return str;

         }



         gboolean gtk_application_quit_callback(gpointer p)
         {

            auto* pgapplication = (GApplication*)p;

            g_application_quit(pgapplication);

            return FALSE;

         }


         void windowing::windowing_post_quit()
         {

            information("windowing::windowing_post_quit");

            g_idle_add(gtk_application_quit_callback, G_APPLICATION(m_pgtkapplication));

         }


         void windowing::user_send(const ::procedure& procedure)
         {

            if (::is_main_thread())
            {

               procedure();

               return;

            }

            //__matter_send_procedure(this, this, &node::node_post, procedure);

            //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
            //      {

            auto pevent = allocateø manual_reset_happening();

            user_post([ procedure, pevent ]
            {

               procedure();

               pevent->set_happening();

            });

            if (!pevent->wait(procedure.timeout()))
            {

               if (::task_get_run())
               {
                  throw ::exception(error_timeout);
               }
               else
               {

                  information() << "thread terminating?!?!";

               }
               //pevent.release();

               //return false;

            }

            ///return true;
            //
            //      }


         }


         // The function to be called in the main thread
         static gboolean execute_on_main_thread(gpointer data)
         {

            auto* pprocedure = (::procedure*)data;

            (*pprocedure)();

            delete pprocedure;

            return FALSE;
         }


         void windowing::user_post(const ::procedure& procedure)
         {

            // Safely update the GTK label in the main thread
            g_main_context_invoke(NULL, execute_on_main_thread, øraw_new ::procedure(procedure));

         }


         void windowing::_on_gtk_application_startup()
         {


            g_unix_fd_add(
   termination_handler::notification_fd(),
   G_IO_IN,
   [](gint, GIOCondition condition, gpointer) -> gboolean
   {
      if (condition & G_IO_IN)
      {
         if (termination_handler::consume())
         {
            // GTK 4:
            //g_application_quit(g_application_get_default());
            ::system()->m_papplication->set_finish();

            // GTK 3 without GApplication might instead use:
            // gtk_main_quit();
         }
      }

      return G_SOURCE_CONTINUE;
   },
   nullptr);

         }


         void windowing::_on_gtk_application_activate()
         {

            m_papplication->post_request(nullptr);

         }


         void windowing::_on_gtk_application_open(const ::pointer_array < ::file::file > & filea)
         {

            auto prequest = create_newø<::request>();

            prequest->m_ecommand = ::e_command_file_open;

            for (auto & pfile : filea)
            {

               prequest->m_payloadFile.payload_array_reference().add(pfile);

            }

            _post_request(prequest);

         }





         // void windowing::hook_operating_ambient_theme_change_callbacks()
         // {
         //
         //
         //
         // }
         //

         // void windowing::_on_activate_gtk_application()
         // {
         //
         //    ::information() << "gtk4::acme::windowing::windowing::_on_activate_gtk_application";
         //
         //    if (m_callbackOnActivateGtkApplication)
         //    {
         //
         //       m_callbackOnActivateGtkApplication();
         //
         //       return;
         //
         //    }
         //
         //    //system()->defer_post_initial_request();
         //
         //    //system()->post_aaa_application_start();
         //    //system()->defer_post_aaa_application_start_file_open_request();
         //    //system()->post_aaa_application_started();
         //
         //    //windowing_application_on_start();
         //
         //    on_activate();
         //
         //    if (!m_bIsGtk4ApplicationHeld)
         //    {
         //
         //       m_bIsGtk4ApplicationHeld = true;
         //
         //       g_application_hold(G_APPLICATION(m_pgtkapplication));
         //
         //    }
         //
         //    if (!m_bApplicationActivated)
         //    {
         //
         //       m_bApplicationActivated = true;
         //
         //       _hook_system_theme_change_callbacks();
         //
         //       fetch_dark_mode();
         //
         //       auto prequestDefaultStart = create_newø<::request>();
         //
         //       prequestDefaultStart->m_ecommand = e_command_default_start;
         //
         //       m_papplication->post_request(prequestDefaultStart);
         //
         //    }
         //
         // }

      } // namespace windowing


   } // namespace acme


} // namespace g



CLASS_DECL_ACME_WINDOWING_G GtkWidget * as_gtk_widget(const ::operating_system::window & operatingsystemwindow)
{

   if (operatingsystemwindow.m_eoperatingambient != ::windowing::e_operating_ambient_gnome)
   {

      throw ::exception(error_bad_argument);

   }

   return (GtkWidget *) operatingsystemwindow.m_opaque.m_ulla[0];

}


CLASS_DECL_ACME_WINDOWING_G ::operating_system::window as_operating_system_window(GtkWidget * pgtkwidget)
{

   return { ::windowing::e_operating_ambient_gnome, (::u64) pgtkwidget};

}