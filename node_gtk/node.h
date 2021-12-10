//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace node_gtk
{


   class CLASS_DECL_ACME node :
      virtual public ::windowing_x11::node
   {
   public:


      gpointer m_pGtkSettingsDefault;


      node();
      ~node() override;


      virtual ::os_theme_colors * _new_os_theme_colors(string strTheme);

      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void defer_notify_startup_complete() override;

      virtual ::e_status start_node() override;

      virtual ::e_status initialize(::object * pobject) override;

      void fetch_user_color() override;

      virtual string os_get_user_theme() override;

      virtual string _os_get_user_theme();

      virtual ::e_status system_main() override;

      //virtual void _on_user_theme_changed() override;

      bool is_branch_current() const override;

      ::e_status os_set_user_theme(const string & strUserTheme) override;

      virtual ::e_status _os_set_user_theme(const string & strUserTheme);

      virtual void os_process_user_theme(string strTheme) override;

      virtual void enable_wallpaper_change_notification() override;

      virtual string get_file_icon_path(const ::string & strPath, int iSize) override;

      virtual string get_file_content_type(const ::string & strPath) override;

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      virtual string get_wallpaper(index iScreen) override;

      using ::aura::node::node_fork;

      virtual bool windowing_message_loop_step();

      virtual ::e_status node_post(const ::routine & routine);

      ///virtual void node_post_quit() override;

      //virtual void on_subject(::promise::subject * psubject, ::context * pcontext) override;

      //virtual void _on_change_os_user_theme(string strTheme);

      virtual void _os_process_user_theme_color(string strTheme);

      //virtual ::node_linux::appindicator * appindicator_allocate() override;

      //virtual void appindicator_destroy(::freebsd::appindicator * pappindicator) override;

      //virtual void enum_display_monitors(::aura::session * psession) override;

      //virtual bool _os_calc_system_dark_mode() override;

      virtual void node_quit() override;

      virtual bool should_launch_on_node(::subject * psubject);

      virtual bool launch_on_node(::subject * psubject);

      virtual int os_launch_uri(const ::string & strUri, char * pszError = NULL, int iBufferSize = 0) override;


   };


} // namespace node_gtk



