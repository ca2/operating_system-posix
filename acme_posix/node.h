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


         //gpointer m_pGtkSettingsDefault;
         string m_strTheme;


         node();
         virtual ~node();


         ::e_status call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
         ::e_status call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set) override;


         ::e_status shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout );

         //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;

         virtual int node_init_check(int * pi, char *** ppz) override;

         //virtual ::e_status start_node();

         //override;

         virtual ::e_status initialize(::object * pobject) override;

   //      virtual ::e_status get_system_time(system_time_t * psystemtime)
   //
   //      override;
   //
   //      virtual double get_time_zone();
   //
   //      virtual ::e_status system_time_to_time(time_t * ptime, const system_time_t * psystime, i32 nDST = -1)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_time(time_t * ptime, const filetime_t * pfiletime, i32 nDST = -1)
   //
   //      override;
   //
   //      virtual ::e_status time_to_system_time(system_time_t * psystemtime, const time_t * ptime)
   //
   //      override;
   //
   //      virtual ::e_status get_system_time_as_file_time(filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status system_time_to_tm(tm * ptm, const system_time_t * psystemtime);
   //
   //      virtual ::e_status tm_to_system_time(system_time_t * psystemtime, const tm * ptm);
   //
   //      virtual ::e_status system_time_to_file_time(filetime_t * pfiletime, const system_time_t * psystemtime)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_local_file_time(filetime_t * pfiletimeLocal, const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status is_valid_filetime(const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual filetime get_filetime_now();


         virtual ::e_status install_sigchld_handler() override;

         bool is_process_running(::u32 pid) override;

         ::e_status create_process(const char * pszCommandLine, u32 * pprocessID) override;

         ::e_status run_silent(const char* strFunct, const char* strstrParams) override;

         bool process_modules(string_array& stra, u32 processID) override;

         bool load_modules_diff(string_array& straOld, string_array& straNew, const char* pszExceptDir) override;

         id_array get_pids() override;

         id_array module_path_get_pid(const char* pszModulePath, bool bModuleNameIsPropertyFormatted) override;

         string module_path_from_pid(u32 pid) override;

         string command_line_from_pid(u32 pid) override;

         bool is_shared_library_busy(u32 processid, const string_array& stra) override;

         bool is_shared_library_busy(const string_array& stra) override;

         bool process_contains_module(string& strImage, ::u32 processID, const char* pszLibrary) override;

         void shared_library_process(dword_array& dwa, string_array& straProcesses, const char* pszLibrary) override;

         string get_environment_variable(const char* pszEnvironmentVariable) override;

         string expand_env(string str) override;


#ifdef POSIX_LIST_SERIAL_PORTS


         virtual array <::serial::port_info> list_serial_ports();


#endif


      };


   } // namespace posix


} // namespace acme



