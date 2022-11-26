//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "apex_posix/node.h"
#include "aura/platform/node.h"


namespace aura_posix
{


   class CLASS_DECL_AURA_POSIX node :
      virtual public ::apex_posix::node,
      virtual public ::aura::node
   {
   public:


#if defined(WITH_X11) || defined(WITH_XCB)


      void *                                 m_pX11Display;


#endif


#if defined(WITH_XCB)


      void *                                 m_pxcbconnection;


#endif


      node();
      ~node() override;


      void initialize(::particle * pparticle) override;



      //void on_initialize_particle() override;
      //::string system_options_html() override;
      //void set_application_menu(application_menu * pmenu, ::apex::application * papp) override;
      //void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      //void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set) override;
      //int node_init_check(int * pi, char *** ppz) override;
      //void reboot() override;
      //void start_node() override;
      //void install_sigchld_handler() override;
      //void on_operating_system_user_theme_change() override;
      //void on_operating_system_user_color_change() override;
      //void on_operating_system_font_list_change() override;
      //void node_post(const ::function < void() > & function) override;
      //void create_process(const string_base<char> & str, unsigned int * puId) override;
      //void run_silent(const string_base<char> & str1, const string_base<char> & str2) override;
      //bool process_modules(string_array & stra, u32 processID) override;
      //bool load_modules_diff(string_array & straOld, string_array & straNew, const ::string & pszExceptDir) override;
      //atom_array get_pids() override;
      //atom_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;
      //string module_path_from_pid(u32 pid) override;
      //string command_line_from_pid(u32 pid) override;
      //bool is_shared_library_busy(u32 processid, const string_array & stra) override;
      //bool is_shared_library_busy(const string_array & stra) override;
      //bool process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary) override;
      //void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary) override;
      //bool is_process_running(::u32 pid) override;
      //string get_environment_variable(const ::string & pszEnvironmentVariable) override;
      //string expand_environment_variables(const ::string & str) override;

      //void delete_this() override;


#if defined(WITH_X11) || defined(WITH_XCB)

      virtual ::e_status _allocate_Display_and_connection();

      void * _get_Display();

      void * get_os_xcb_connection() override;

      bool has_xcb() const override;

#endif // WITH_X11 || WITH_XCB



#if defined(WITH_XCB)

      /// ^ ^^^

      void * _get_connection();


#endif // WITH_XCB


      ::file::path get_desktop_file_path(::apex::application * papp) override;


      void main() override;


   };


} // namespace aura_posix



