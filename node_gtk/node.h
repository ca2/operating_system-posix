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

      int node_init_check(int * pi, char *** ppz) override;

      void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::object * pobject) override;

      void fetch_user_color() override;

      string os_get_user_theme() override;

      virtual string _os_get_user_theme();

      void system_main() override;

      bool is_branch_current() const override;

      void os_set_user_theme(const string & strUserTheme) override;

      virtual ::e_status _os_set_user_theme(const string & strUserTheme);

      void os_process_user_theme(string strTheme) override;

      void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::string & strPath, int iSize) override;

      string get_file_content_type(const ::string & strPath) override;

      bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      string get_wallpaper(index iScreen) override;

      using ::aura::node::node_post;

      virtual bool windowing_message_loop_step();

      void node_post(const ::procedure & procedure) override;

      virtual void _os_process_user_theme_color(string strTheme);

      void node_quit() override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      int os_launch_uri(const ::string & strUri, char * pszError = NULL, int iBufferSize = 0) override;


   };


} // namespace node_gtk



