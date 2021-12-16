//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#ifdef WITH_XCB
#include <X11/Xlib-xcb.h>
#endif


namespace aura
{


   namespace posix
   {


      node::node()
      {

#if defined(WITH_X11) || defined(WITH_XCB)
         
         
         m_pX11Display = nullptr;

#endif // WITH_X11 || WITH_XCB


#if defined(WITH_XCB)

         m_pxcbconnection = nullptr;
         
#endif

         m_pAuraPosix = this;

      }


      node::~node()
      {

         //      if(m_pGtkSettingsDefault)
         //      {
         //
         //         g_object_unref(m_pGtkSettingsDefault);
         //
         //      }

      }

//
//      ::extended::transport<appindicator> node::new_appindicator()
//      {
//
//         auto pappindicator = __create<appindicator>();
//
//         if (!pappindicator)
//         {
//
//            return pappindicator;
//
//         }
//
//         return pappindicator;
//
//      }


      //   int node::node_init_check(int *pi, char ***ppz)
      //   {
      //
      //      auto iResult = gtk_init_check(pi, ppz);
      //
      //      return iResult;
      //
      //   }


//      ::e_status node::start()
//      {
//
//
//         //      if (System.m_bGtkApp)
//         //      {
//         //
//         //         apex_application_run(System.m_XstrAppId, System.m_strProgName);
//         //
//         //      }
//         //      else
//         //      {
//         //      //
//         //      ////      g_set_application_name(psystem->m_XstrAppId);
//         //      ////
//         //      ////      g_set_prgname(psystem->m_strProgName);
//         //      ////
//         //      ////      //auto idle_source = g_idle_source_new();
//         //      ////
//         //      ////      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) m_psystem, nullptr);
//         //      ////
//         //      ////      //g_source_attach(idle_source, g_main_context_default());
//         //      ////
//         //      ////      //int c = 2;
//         //      ////
//         //      ////      //const char * argv[]={"app", "--g-fatal-warnings"};
//         //      ////
//         //      ////#if !defined(__SANITIZE_ADDRESS__)
//         //      ////
//         //      ////      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
//         //      ////
//         //      ////#endif
//         //
//         //         node_fork([this]()
//         //                   {
//         //
//         //                      //x11_add_idle_source();
//         //
//         //                      //x11_add_filter();
//         //
//         //                      auto pgtksettingsDefault = gtk_settings_get_default();
//         //
//         //                      if(pgtksettingsDefault)
//         //                      {
//         //
//         //
//         //                         m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);
//         //
//         //                         g_object_ref (m_pGtkSettingsDefault);
//         //
//         //                         gchar *theme_name = nullptr;
//         //
//         //                         g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);
//         //
//         //                         m_strTheme = theme_name;
//         //
//         //                         g_free(theme_name);
//         //
//         //                         auto preturn = g_signal_connect_data(
//         //                            m_pGtkSettingsDefault,
//         //                            "notify::gtk-theme-name",
//         //                            G_CALLBACK(gtk_settings_gtk_theme_name_callback),
//         //                            this,
//         //                            NULL,
//         //                            G_CONNECT_AFTER);
//         //
//         //                         //g_object_ref(preturn);
//         //
//         //                         //printf("return %" PRIiPTR, preturn);
//         //
//         //                         //printf("return %" PRIiPTR, preturn);
//         //
//         //                      }
//         //
//         //
//         //                   });
//         //
//         //
//         //         //x11_add_filter();
//         //
//         //System.fork([]()
//         //     {
//         //
//         //      x11_main();
//         //
//         //     });
//         //
//         //         gtk_main();
//         //
//         //         //x11_main();
//         //
//         //      }
//         //      //
//         //      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());
//
//         return ::success;
//
//      }


      ::e_status node::initialize(::object * pobject)
      {

         auto estatus = ::apex::posix::node::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

#if defined(WITH_X11) || defined(WITH_XCB)

         estatus = _allocate_Display_and_connection();

         if(!estatus)
         {

            INFORMATION("Failed to _allocate_Display_and_connection");

            return estatus;

         }
         
#endif // WITH_X11

         return estatus;

      }

   
#if defined(WITH_X11) || defined(WITH_XCB)
   

      ::e_status node::_allocate_Display_and_connection()
      {

         m_pX11Display = XOpenDisplay(nullptr);

         if(!m_pX11Display)
         {

            return error_failed;

         }

#if defined(WITH_XCB)

         m_pxcbconnection = XGetXCBConnection((Display *) m_pX11Display);

         if(!m_pxcbconnection)
         {

            return error_failed;

         }

#endif

         return ::success;

      }

   
      void * node::_get_Display()
      {

         return m_pX11Display;

      }


#if defined(WITH_XCB)

      void * node::_get_connection()
      {

         return m_pxcbconnection;

      }

#endif
   
#endif
   

      ::file::path node::get_desktop_file_path(::application * papplication) const
      {

         ::file::path path;

         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

         path = pacmedir->home();

         path /= ".local/share/applications";

         string strApplicationServerName = papplication->m_strAppId;

         strApplicationServerName.replace("/", ".");

         strApplicationServerName.replace("_", "-");

         path /= (strApplicationServerName + ".desktop");

         return path;

      }


      ::e_status node::main()
      {

         auto estatus = system_main();

         if(!estatus)
         {

            return estatus;

         }

         //auto psystem = m_psystem;

         //auto estatus = psystem->system_main();

         //if(!estatus)
         //{

           // return estatus;

         //}

         return estatus;

      }


   } // namespace posix


} // namespace aura



