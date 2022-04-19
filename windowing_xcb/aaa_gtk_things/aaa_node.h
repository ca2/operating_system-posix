//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace node_gnome
{


   class CLASS_DECL_ACME node :
      virtual public ::aura::node
   {
   public:


      gpointer m_pGtkSettingsDefault;
      string   m_strTheme;

      node();
      virtual ~node();


      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void os_application_system_run() override;

      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual void os_calc_user_dark_mode() override;

      virtual string os_get_user_theme() override;

      virtual bool os_set_user_theme(const string & strUserTheme) override;

      virtual void os_process_user_theme(string strTheme) override;

      virtual void enable_wallpaper_change_notification() override;

      virtual string get_file_icon_path(const char * pszPath, int iSize) override;

      virtual string get_file_content_type(const char * pszPath) override;

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      virtual string get_wallpaper(index iScreen) override;

      using ::aura::node::node_fork;

      virtual void node_fork(const ::promise::procedure & routine) override;

      virtual void node_post_quit() override;

      virtual ::freebsd::appindicator * appindicator_allocate() override;

      virtual void appindicator_destroy(::freebsd::appindicator * pappindicator) override;

      //virtual void enum_display_monitors(::aura::session * psession) override;

      virtual void os_post_quit() override;

      virtual bool should_launch_on_node(::promise::topic * ptopic);

      virtual bool launch_on_node(::promise::topic * ptopic);


   };


} // namespace node_gnome




