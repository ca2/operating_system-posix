//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "apex_posix/node.h"
#include "aura/platform/node.h"


struct wl_display;


namespace aura_posix
{


   class CLASS_DECL_AURA_POSIX node :
      virtual public ::apex_posix::node,
      virtual public ::aura::node
   {
   public:

#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)


#if defined(WITH_X11) || defined(WITH_XCB)


       void *                                 m_pAuraPosixX11Display;


#endif


#if defined(WITH_XCB)


      void *                                 m_pAuraPosixXcbConnection;


#endif

#endif


      node();
      ~node() override;


      void initialize(::particle * pparticle) override;

virtual void initialize_window_manager();
      virtual ::wl_display * get_wayland_display();
      //void on_initialize_particle() override;
      //::string system_options_html() override;
      //void set_application_menu(application_menu * pmenu, ::apex::application * papp) override;
      //void call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      //void call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set) override;
      //void reboot() override;
      //void start_node() override;
      //void install_sigchld_handler() override;
      //void on_operating_system_user_theme_change() override;
      //void on_operating_system_user_color_change() override;
      //void on_operating_system_font_list_change() override;
      //void node_post(const ::function < void() > & function) override;
      //void create_process(const string_base<char> & str, unsigned int * puId) override;
      //void run_silent(const string_base<char> & str1, const string_base<char> & str2) override;
      //bool process_modules(string_array_base & stra, unsigned int processID) override;
      //bool load_modules_diff(string_array_base & straOld, string_array_base & straNew, const ::scoped_string & scopedstrExceptDir) override;
      //atom_array get_pids() override;
      //atom_array module_path_get_pid(const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted) override;
      //string module_path_from_pid(unsigned int pid) override;
      //string command_line_from_pid(unsigned int pid) override;
      //bool is_shared_library_busy(unsigned int processid, const string_array_base & stra) override;
      //bool is_shared_library_busy(const string_array_base & stra) override;
      //bool process_contains_module(string & strImage, unsigned int processID, const ::scoped_string & scopedstrLibrary) override;
      //void shared_library_process(dword_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrLibrary) override;
      //bool is_process_running(unsigned int pid) override;
      //string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;
      //string expand_environment_variables(const ::scoped_string & scopedstr) override;

#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
#if defined(WITH_X11) || defined(WITH_XCB)

      virtual ::e_status _allocate_Display_and_connection();

      void * _get_Display();

      void * get_os_xcb_connection() override;

      bool has_xcb() override;

      //bool is_wayland() const override;

#endif // WITH_X11 || WITH_XCB



#if defined(WITH_XCB)

      /// ^ ^^^

      void * _get_connection();


#endif // WITH_XCB
#endif

      ::file::path get_desktop_file_path(::apex::application * papp) override;
      virtual ::file::path get_desktop_file_path_by_app_id(const ::scoped_string & scopedstrAppId);


      //void on_request(::request * prequest) override;


      void main() override;


      void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;


   };


} // namespace aura_posix





