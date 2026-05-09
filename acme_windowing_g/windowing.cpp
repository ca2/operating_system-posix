//
// Created by camilo on 4/2/26.
//
//
// Created by camilo on 2024-04-02 01:39 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/handler/request.h"
#include "acme/platform/application.h"


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
