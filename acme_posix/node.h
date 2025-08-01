//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme/platform/node.h"


namespace acme_posix
{


   class CLASS_DECL_ACME node :
      virtual public ::platform::node
   {
   public:


      node();
      ~node() override;


      void dbus_init();

      void initialize(::particle * pparticle) override;

      void install_sigchld_handler() override;


       //bool _is_dropbox_installed() override;

       //void calculate_dropbox_installed() override;


      // defined at process.cpp
      void call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode) override;
      ::process_identifier create_process(const ::scoped_string & scopedstrCommandLine) override;
      virtual int _create_process3(const ::string & _cmd_line, int * pprocessId);
      void run_silent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams) override;
      //::e_status shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, class ::time timeTimeout) override;


      // defined at process.cpp
      ::file::path process_identifier_module_path(::process_identifier pid) override;
      ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted) override;
      string process_identifier_command_line(process_identifier pid) override;
      //bool is_shared_library_busy(process_identifier processid, const string_array & stra) override;
      //bool is_shared_library_busy(const string_array & stra) override;


      bool is_process_running(process_identifier pid) override;

      ::file::path_array process_identifier_modules_paths(process_identifier processidentifier) override;

      bool load_modules_diff(string_array& straOld, string_array& straNew, const ::scoped_string & scopedstrExceptDir) override;

      ::process_identifier_array processes_identifiers() override;

      ::process_identifier current_process_identifier() override;
      
      ::pointer < ::mutex > create_local_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes = nullptr) override;
      ::pointer < ::mutex > create_global_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes = nullptr) override;

      ::pointer<::mutex> open_named_mutex(::particle * pparticle, const_char_pointer lpszName);

      ::pointer < ::mutex > open_local_named_mutex(::particle * pparticleContext, const ::scoped_string & scopedstrName) override;
      ::pointer < ::mutex > open_global_named_mutex(::particle * pparticleContext, const ::scoped_string & scopedstrName) override;

      ::pointer < ::acme::exclusive > get_exclusive(::particle * pparticleContext, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes = nullptr) override;

      bool process_contains_module(string& strImage, ::process_identifier processID, const ::scoped_string & scopedstrLibrary) override;

      ::process_identifier_array shared_library_process(string_array& straProcesses, const ::scoped_string & scopedstrLibrary) override;

      string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;

      void set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string & scopedstrPayload) override;

      void unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;

      string expand_environment_variables(const ::scoped_string & scopedstr) override;


      virtual bool posix_try_open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::string_array & straBrowsers);


      bool stdin_has_input_events() override;

      //bool stdin_wait_char();

      void flush_stdin() override;

      virtual array <::serial::port_info> list_serial_ports() override;

      void reboot() override;


      virtual int _get_proc_stat_core_count();


      //void aaa_user_post(const ::procedure & procedure) override;

//#if defined(__clang__) && !defined(__ANDROID__)
//      ::string get_callstack() override;
//#endif

      bool set_process_priority(::enum_priority epriority) override;


      //void command_system(string_array & straOutput, int& iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem, const class ::time& timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLog) override;
      virtual int __command_system(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPipe, const trace_function & tracefunction = nullptr);
      int command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction = nullptr, const ::file::path & pathWorkingDirectory ={}, ::e_display edisplay = e_display_none) override;


      void launch_process(const ::scoped_string & scopedstr) override;

      ::file::path library_file_name(const ::scoped_string& scopedstr) override;


      int posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell = e_posix_shell_system_default, const trace_function& tracefunction = nullptr) override;

      //::user::enum_operating_ambcient calculate_edesktop() override;

      bool is_executable_in_path(const ::scoped_string & scopedstr) override;

      void integration_factory() override;

      bool has_command(const ::scoped_string& scopedstrCommand) override;


      void detached_command(const ::scoped_string & scopedstrCommand, const ::file::path & pathLog) override;

      bool _is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath = nullptr, const_char_pointer pszPath = nullptr) override;

      //enum_windowing calculate_ewindowing() override;

      bool _is_jetbrains_clion_installed() override;

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)

      bool _is_smart_git_installed() override;

      
#endif
      
      bool _is_git_credential_manager_installed() override;

      int synchronous_posix_terminal(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell, const trace_function& tracefunction) override;

      bool _is_google_chrome_installed() override;

      bool _is_visual_studio_code_installed() override;


      //void do_windowing_system_factory() override;


      void on_system_main() override;


      ::string default_component_implementation(const ::scoped_string & scopedstrComponentName) override;

      ::string get_computer_name() override;

      // node_utsname.cpp
      virtual ::string _uname_system();
      virtual ::string _uname_release();
      virtual ::string _uname_machine();


      ::string system_name() override;
      ::string system_release() override;
      ::string system_architecture() override;


      ::string dynamic_library_prefix() override;
      ::string dynamic_library_suffix() override;



   };

   
} // namespace acme_posix



