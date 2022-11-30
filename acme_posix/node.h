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
      virtual public ::acme::node
   {
   public:


      string m_strTheme;


      node();
      ~node() override;


      int node_init_check(int * pi, char *** ppz) override;

      void dbus_init();

      void initialize(::particle * pparticle) override;

      void install_sigchld_handler() override;



      // defined at process.cpp
      void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode) override;
      void create_process(const ::string & pszCommandLine, u32 * pprocessID) override;
      virtual i32 _create_process3(const ::string & _cmd_line, i32 * pprocessId);
      void run_silent(const ::string & strFunct, const ::string & strstrParams) override;
      //::e_status shell_execute_sync(const ::string & pszFile, const ::string & pszParams, class ::time timeTimeout) override;


      // defined at process.cpp
      string module_path_from_pid(u32 pid) override;
      atom_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;
      string command_line_from_pid(u32 pid) override;
      bool is_shared_library_busy(u32 processid, const string_array & stra) override;
      bool is_shared_library_busy(const string_array & stra) override;


      bool is_process_running(::u32 pid) override;

      bool process_modules(string_array& stra, u32 processID) override;

      bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;

      atom_array get_pids() override;


      ::pointer < ::mutex > create_local_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr) override;
      ::pointer < ::mutex > create_global_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr) override;

      ::pointer<::mutex> open_named_mutex(::particle * pparticle, const char * lpszName);

      ::pointer < ::mutex > open_local_named_mutex(::particle * pparticleContext, const ::string & strName) override;
      ::pointer < ::mutex > open_global_named_mutex(::particle * pparticleContext, const ::string & strName) override;

      ::pointer < ::acme::exclusive > get_exclusive(::particle * pparticleContext, const ::string & strName, security_attributes * psecurityattributes = nullptr) override;

      bool process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary) override;

      void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary) override;

      string get_environment_variable(const ::string & pszEnvironmentVariable) override;

      string expand_environment_variables(const ::string & str) override;

      bool stdin_has_input_events() override;

      //bool stdin_wait_char();

      void flush_stdin() override;

#ifdef POSIX_LIST_SERIAL_PORTS

      virtual array <::serial::port_info> list_serial_ports();


#endif

      void reboot() override;


      virtual int _get_proc_stat_core_count();


      void node_post(const ::procedure & procedure) override;

//#if defined(__clang__) && !defined(ANDROID)
//      ::string get_callstack() override;
//#endif

      //bool set_process_priority(::enum_priority epriority) override;


      void command_system(string_array & straOutput, int& iExitCode, const char* psz, enum_command_system ecommandsystem, const class ::time& timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLog) override;


   };

   
} // namespace acme_posix



