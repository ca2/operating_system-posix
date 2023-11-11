//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
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
         
         
      m_pAuraPosixX11Display = nullptr;

#endif // WITH_X11 || WITH_XCB


#if defined(WITH_XCB)

      m_pAuraPosixXcbConnection = nullptr;
         
#endif

      m_edisplaytype = e_display_type_none;

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



   void node::initialize(::particle * pparticle)
   {

      information() << "aura_posix::node initialize";

      ::apex_posix::node::initialize(pparticle);

#if defined(WITH_X11) || defined(WITH_XCB)

      information() << "aura_posix::node initialize going to call _allocate_Display_and_connection";

      _allocate_Display_and_connection();

#endif // WITH_X11

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

   //void node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   //{

   //   ::apex::posix::node::call_async(pszPath, pszParam, pszDir, edisplay, bPrivileged, puiPid);

   //}

   //
   //void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
   //{

   //   ::apex::posix::node::call_sync(pszPath, pszParam, pszDir, edisplay, timeTimeout, set);

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

      m_pAuraPosixX11Display = XOpenDisplay(nullptr);

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
   

   ::file::path node::get_desktop_file_path(::apex::application * papp)
   {

      return get_desktop_file_path_by_app_id(papp->m_strAppId);

   }


   ::file::path node::get_desktop_file_path_by_app_id(const ::scoped_string & scopedstrAppId)
   {

      ::file::path path;

      path = acmedirectory()->home();

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

#if defined(LINUX)

      ::file::path path = get_executable_path_by_app_id(scopedstrAppId, bSingleExecutableVersion);

      ::file::path pathFolder = path.folder();

      string strName = path.name();

      ::string strCommand;

      acmedirectory()->change_current(pathFolder);

      ::file::path pathLogFolder;

      pathLogFolder = acmedirectory()->home() / "application" / scopedstrAppId / "log";

      acmedirectory()->create(pathLogFolder);

      ::string strLogFileName;

      strLogFileName = system()->datetime()->international().get_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE_WITH_NO_SPACES) ;

      strLogFileName += ".txt";

      ::file::path pathLog;

      pathLog = pathLogFolder / strLogFileName;

      strCommand = "sh -c \"nohup ./\\\"" + strName + "\\\" > \\\"" + pathLog +"\\\"\"";

      information() << "node::launch_app_by_app_id : " << strCommand;

      int iExitCode = acmenode()->command_system(strCommand, 10_minutes);

      if(iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

#endif

   }


} // namespace aura_posix



