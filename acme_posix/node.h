//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{


   namespace posix
   {


      class CLASS_DECL_ACME node :
         virtual public ::acme::node
      {
      public:

         //__creatable_from_library(node, ::acme::node, "acme_posix");

         string m_strTheme;


         node();
         ~node() override;


         void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
         void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set) override;


         ::e_status shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout );

         virtual int node_init_check(int * pi, char *** ppz) override;

         void dbus_init();

         void initialize(::object * pobject) override;

         void install_sigchld_handler() override;

         bool is_process_running(::u32 pid) override;

         void create_process(const ::string & pszCommandLine, u32 * pprocessID) override;

         void run_silent(const ::string & strFunct, const ::string & strstrParams) override;
         
         virtual i32 _create_process3(const ::string & _cmd_line, i32 * pprocessId);

         bool process_modules(string_array& stra, u32 processID) override;

         bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;

         id_array get_pids() override;

         id_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;

         string module_path_from_pid(u32 pid) override;

         string command_line_from_pid(u32 pid) override;

         bool is_shared_library_busy(u32 processid, const string_array& stra) override;

         bool is_shared_library_busy(const string_array& stra) override;

         bool process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary) override;

         void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary) override;

         string get_environment_variable(const ::string & pszEnvironmentVariable) override;

         string expand_environment_variables(const ::string & str) override;


#ifdef POSIX_LIST_SERIAL_PORTS


         virtual array <::serial::port_info> list_serial_ports();


#endif

         void reboot() override;


         virtual int _get_proc_stat_core_count();


         void node_post(const ::routine & routine) override;


      };


   } // namespace posix


} // namespace acme



