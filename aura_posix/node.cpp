//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/system.h"
#include "apex/platform/application.h"
#ifdef WITH_X11
#include <X11/Xlib.h>
#endif
#ifdef WITH_XCB
#include <X11/Xlib-xcb.h>
#endif



namespace aura_posix
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
//         //      ////      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) acmesystem(), nullptr);
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


   void node::initialize(::particle * pparticle)
   {

      //auto estatus =
      //
      ::apex_posix::node::initialize(pparticle);

//         if (!estatus)
//         {
//
//            return estatus;
//
//         }

#if defined(WITH_X11) || defined(WITH_XCB)

      //estatus =
      //
      _allocate_Display_and_connection();

//         if(!estatus)
//         {
//
//            INFORMATION("Failed to _allocate_Display_and_connection");
//
//            return estatus;
//
//         }
         
#endif // WITH_X11

      //return estatus;

   }

   
   //void node::on_initialize_particle()
   //{

   //   ::aura::node::on_initialize_particle();

   //   ::apex::posix::node::on_initialize_particle();

   //}

   //
   //::string node::system_options_html()
   //{

   //   return ::aura::node::system_options_html();

   //}


   //void node::set_application_menu(application_menu * pmenu, ::apex::application * papp)
   //{

   //   ::aura::node::set_application_menu(pmenu, papp);

   //}
   //

   //void node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   //{

   //   ::apex::posix::node::call_async(pszPath, pszParam, pszDir, edisplay, bPrivileged, puiPid);

   //}

   //
   //void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
   //{

   //   ::apex::posix::node::call_sync(pszPath, pszParam, pszDir, edisplay, timeTimeout, set);

   //}


   //int node::node_init_check(int * pi, char *** ppz)
   //{

   //   return ::apex::posix::node::node_init_check(pi, ppz);

   //}

   //void node::reboot()
   //{

   //   ::apex::posix::node::reboot();

   //}

   //void node::start_node()
   //{

   //   ::apex::posix::node::start_node();

   //}

   //void node::install_sigchld_handler()
   //{

   //   ::apex::posix::node::install_sigchld_handler();

   //}


   //void node::on_operating_system_user_theme_change()
   //{

   //   ::apex::posix::node::on_operating_system_user_theme_change();

   //}


   //void node::on_operating_system_user_color_change()
   //{

   //   ::apex::posix::node::on_operating_system_user_color_change();

   //}


   //void node::on_operating_system_font_list_change()
   //{

   //   ::apex::posix::node::on_operating_system_font_list_change();

   //}


   //void node::node_post(const ::function < void() > & function)
   //{

   //   ::aura::node::node_post(function);

   //}


   //void node::create_process(const string_base<char> & str, unsigned int * puId)
   //{

   //   ::apex::posix::node::create_process(str, puId);

   //}


   //void node::run_silent(const string_base<char> & str1, const string_base<char> & str2)
   //{

   //   ::apex::posix::node::run_silent(str1, str2);

   //}


   //bool node::process_modules(string_array & stra, u32 processID)
   //{

   //   return ::apex::posix::node::process_modules(stra, processID);

   //}
   //   
   //bool node::load_modules_diff(string_array & straOld, string_array & straNew, const ::string & pszExceptDir)

   //{

   //   return ::apex::posix::node::load_modules_diff(straOld, straNew, pszExceptDir);
   //}

   //   atom_array node::get_pids()
   //{

   //   return ::apex::posix::node::get_pids();


   //}

   //atom_array node::module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted)
   //{

   //   return ::apex::posix::node::module_path_get_pid(pszModulePath, bModuleNameIsPropertyFormatted);

   //}


   //string node::module_path_from_pid(u32 pid)
   //{

   //   return ::apex::posix::node::module_path_from_pid(pid);

   //}
   //
   //
   //string node::command_line_from_pid(u32 pid)
   //{

   //   return ::apex::posix::node::command_line_from_pid(pid);

   //}
   //   bool node::is_shared_library_busy(u32 processid, const string_array & stra)
   //{

   //   return ::apex::posix::node::is_shared_library_busy(processid, stra);

   //}

   //   bool node::is_shared_library_busy(const string_array & stra)
   //{

   //   return ::apex::posix::node::is_shared_library_busy(stra);

   //}
   //   bool node::process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary)
   //{

   //   return ::apex::posix::node::process_contains_module(strImage, processID, pszLibrary);

   //}

   //void node::shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary)
   //{

   //   ::apex::posix::node::shared_library_process(dwa, straProcesses, pszLibrary);

   //}
   //
   //
   //bool node::is_process_running(::u32 pid)
   //{

   //   return ::apex::posix::node::is_process_running(pid);

   //}
   //string node::get_environment_variable(const ::string & pszEnvironmentVariable)
   //{

   //   return ::apex::posix::node::get_environment_variable(pszEnvironmentVariable);

   //}

   //string node::expand_environment_variables(const ::string & str)
   //{

   //   return ::apex::posix::node::expand_environment_variables(str);

   //}

   //void node::delete_this()
   //{

   //   ::aura::node::delete_this();

   //}


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


   void * node::get_os_xcb_connection()
   {

#if defined(WITH_XCB)

      return m_pxcbconnection;

#else

      return nullptr;

#endif

   }


   bool node::has_xcb() const
   {

#if defined(WITH_XCB)

      return ::is_set(m_pxcbconnection);

#else

      return false;

#endif

   }


#if defined(WITH_XCB)

   void * node::_get_connection()
   {

      return m_pxcbconnection;

   }

#endif
   
#endif
   

   ::file::path node::get_desktop_file_path(::apex::application * papp)
   {

      ::file::path path;

      path = acmedirectory()->home();

      path /= ".local/share/applications";

      string strApplicationServerName = papp->m_strAppId;

      strApplicationServerName.find_replace("/", ".");

      strApplicationServerName.find_replace("_", "-");

      path /= (strApplicationServerName + ".desktop");

      return path;

   }


   void node::main()
   {

      //auto estatus =


         system_main();
//
//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
//
//         //auto psystem = acmesystem();
//
//         //auto estatus = psystem->system_main();
//
//         //if(!estatus)
//         //{
//
//           // return estatus;
//
//         //}
//
//         return estatus;

   }


} // namespace aura_posix



