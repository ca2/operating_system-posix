//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"
#include "apex/platform/application.h"
#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
#ifdef WITH_X11
#include <X11/Xlib.h>
//::e_status deferx_initializex_x11();
//Display * x11_get_display();
#endif
#ifdef WITH_XCB
#include <X11/Xlib-xcb.h>
#endif
#endif


namespace aura_posix
{


   node::node()
   {

#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
#if defined(WITH_X11) || defined(WITH_XCB)
         
         
      m_pAuraPosixX11Display = nullptr;

#endif // WITH_X11 || WITH_XCB


#if defined(WITH_XCB)

      m_pAuraPosixXcbConnection = nullptr;
         
#endif
#endif
      //m_pAuraPosix = this;

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
//         auto pappindicator = øcreate<appindicator>();
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



   void node::initialize(::particle * pparticle)
   {

      information() << "aura_posix::node initialize";

      ::apex_posix::node::initialize(pparticle);

      initialize_window_manager();

   }


   void node::initialize_window_manager()
   {

#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
#if defined(WITH_X11) || defined(WITH_XCB)

      information() << "aura_posix::node initialize going to call _allocate_Display_and_connection";

      _allocate_Display_and_connection();

#endif // WITH_X11
#endif
   }


   ::wl_display * node::get_wayland_display()
   {

      return nullptr;

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

   //void node::call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   //{

   //   ::apex::posix::node::call_async(scopedstrPath, pszParam, pszDir, edisplay, bPrivileged, puiPid);

   //}

   //
   //void node::call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
   //{

   //   ::apex::posix::node::call_sync(scopedstrPath, pszParam, pszDir, edisplay, timeTimeout, set);

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


   //bool node::process_modules(string_array_base & stra, unsigned int processID)
   //{

   //   return ::apex::posix::node::process_modules(stra, processID);

   //}
   //   
   //bool node::load_modules_diff(string_array_base & straOld, string_array_base & straNew, const ::scoped_string & scopedstrExceptDir)

   //{

   //   return ::apex::posix::node::load_modules_diff(straOld, straNew, pszExceptDir);
   //}

   //   atom_array node::get_pids()
   //{

   //   return ::apex::posix::node::get_pids();


   //}

   //atom_array node::module_path_get_pid(const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted)
   //{

   //   return ::apex::posix::node::module_path_get_pid(scopedstrModulePath, bModuleNameIsPropertyFormatted);

   //}


   //string node::module_path_from_pid(unsigned int pid)
   //{

   //   return ::apex::posix::node::module_path_from_pid(pid);

   //}
   //
   //
   //string node::command_line_from_pid(unsigned int pid)
   //{

   //   return ::apex::posix::node::command_line_from_pid(pid);

   //}
   //   bool node::is_shared_library_busy(unsigned int processid, const string_array_base & stra)
   //{

   //   return ::apex::posix::node::is_shared_library_busy(processid, stra);

   //}

   //   bool node::is_shared_library_busy(const string_array_base & stra)
   //{

   //   return ::apex::posix::node::is_shared_library_busy(stra);

   //}
   //   bool node::process_contains_module(string & strImage, unsigned int processID, const ::scoped_string & scopedstrLibrary)
   //{

   //   return ::apex::posix::node::process_contains_module(strImage, processID, pszLibrary);

   //}

   //void node::shared_library_process(dword_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrLibrary)
   //{

   //   ::apex::posix::node::shared_library_process(dwa, straProcesses, pszLibrary);

   //}
   //
   //
   //bool node::is_process_running(unsigned int pid)
   //{

   //   return ::apex::posix::node::is_process_running(pid);

   //}
   //string node::get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   //{

   //   return ::apex::posix::node::get_environment_variable(scopedstrEnvironmentVariable);

   //}

   //string node::expand_environment_variables(const ::scoped_string & scopedstr)
   //{

   //   return ::apex::posix::node::expand_environment_variables(str);

   //}

#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)

#if defined(WITH_X11) || defined(WITH_XCB)
   

   ::e_status node::_allocate_Display_and_connection()
   {
      
      //deferx_initializex_x11();
      
      auto pacmedisplay = system()->acme_windowing()->acme_display();
      
      if(::is_null(pacmedisplay))
      {
         
         return error_failed;
         
      }




      m_pAuraPosixX11Display = pacmedisplay->raw_x11_display();

      if(!m_pAuraPosixX11Display)
      {

         return error_failed;

      }

      information() << "aura_posix::node::_allocate_Display_and_connection m_pAuraPosixX11Display : " << (::iptr)m_pAuraPosixX11Display;


#if defined(WITH_XCB)

      m_pAuraPosixXcbConnection = XGetXCBConnection((Display *) m_pAuraPosixX11Display);

      if(!m_pAuraPosixXcbConnection)
      {

         return error_failed;

      }

      information() << "aura_posix::node::_allocate_Display_and_connection m_pAuraPosixXcbConnection : " << (::iptr)m_pAuraPosixXcbConnection;

#endif

      return ::success;

   }

   
   void * node::_get_Display()
   {

      return m_pAuraPosixX11Display;

   }


   void * node::get_os_xcb_connection()
   {

#if defined(WITH_XCB)

      return m_pAuraPosixXcbConnection;

#else

      return nullptr;

#endif

   }


   bool node::has_xcb()
   {

#if defined(WITH_XCB)

      return ::is_set(m_pAuraPosixXcbConnection);

#else

      return false;

#endif

   }




#if defined(WITH_XCB)

   void * node::_get_connection()
   {

      return m_pAuraPosixXcbConnection;

   }

#endif
   
#endif
   
#endif


   ::file::path node::get_desktop_file_path(::apex::application * papp)
   {

      return get_desktop_file_path_by_app_id(papp->m_strAppId);

   }


   ::file::path node::get_desktop_file_path_by_app_id(const ::scoped_string & scopedstrAppId)
   {

      ::file::path path;

      path = directory_system()->home();

      path /= ".local/share/applications";

      string strDesktopFileName = scopedstrAppId;

      strDesktopFileName.find_replace("/", ".");

      strDesktopFileName.find_replace("_", "-");

      path /= (strDesktopFileName + ".desktop");

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
//         //auto psystem = system();
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


   void node::launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion)
   {

#if defined(LINUX) || defined(__BSD__)

      ::file::path path = get_executable_path_by_app_id(scopedstrAppId, bSingleExecutableVersion);

      ::file::path pathFolder = path.folder();

      string strName = path.name();

      ::string strCommand;

      directory_system()->change_current(pathFolder);

      ::file::path pathLogFolder;

      pathLogFolder = directory_system()->home() / "application" / scopedstrAppId / "log";

      directory_system()->create(pathLogFolder);

      ::string strLogFileName;

      strLogFileName = datetime()->date_time_text_for_file_with_no_spaces();

      strLogFileName += ".txt";

      ::file::path pathLog;

      pathLog = pathLogFolder / strLogFileName;

      strCommand = "sh -c \"nohup ./\\\"" + strName + "\\\" > \\\"" + pathLog +"\\\"\"";

      information() << "node::launch_app_by_app_id : " << strCommand;

      auto inlinelog = std_inline_log();

      inlinelog.set_timeout(10_minutes);

      int iExitCode = this->command_system(strCommand, inlinelog);

      if(iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

#endif

   }


} // namespace aura_posix







