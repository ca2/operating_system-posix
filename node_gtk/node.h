//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#ifdef G_OS_UNIX
#include <gio/gdesktopappinfo.h>
#endif

#include "acme/primitive/collection/string_map.h"
#include "aura_posix/node.h"




namespace node_gtk
{


   class CLASS_DECL_ACME node :
      virtual public ::aura_posix::node
   {
   public:


      gpointer m_pGtkSettingsDefault;

      GdkAppLaunchContext * m_pgdkapplaunchcontext;
      string_map < GDesktopAppInfo * > m_mapGDesktopAppInfo;

      ::string       m_strOsUserTheme;
      ::string       m_strOsUserIconTheme;

      ::task_pointer       m_ptaskOsUserTheme;
      ::task_pointer       m_ptaskOsUserIconTheme;


      node();
      ~node() override;


      virtual void _set_os_user_theme(const ::scoped_string & strTheme);
      virtual void _apply_os_user_theme();


      virtual void _set_os_user_icon_theme(const ::scoped_string & strIconTheme);
      virtual void _apply_os_user_icon_theme();


      virtual ::os_theme_colors * _new_os_theme_colors(string strTheme);
      virtual void _set_os_theme_colors(::os_theme_colors * posthemecolors);

      int node_init_check(int * pi, char *** ppz) override;

      void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::particle * pparticle) override;

      void fetch_user_color() override;

      string os_get_user_theme() override;

      virtual string _os_get_user_theme();

      void system_main() override;

      bool is_branch_current() const override;

      virtual void _dark_mode();

      bool dark_mode() const override;

      void set_dark_mode(bool bDarkMode) override;

      void os_set_user_theme(const string & strUserTheme) override;

      virtual ::e_status _os_set_user_theme(const string & strUserTheme);

      virtual ::e_status _os_set_user_icon_theme(const string & strUserIconTheme);

      void os_process_user_theme(string strTheme) override;

      void os_process_user_icon_theme(string strTheme) override;

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

      void shell_launch(const ::string & strAppId) override;

      void open_url(const ::string & strUrl) override;

      void _node_file_dialog(::file::file_dialog * pdialog) override;

      void _node_folder_dialog(::file::folder_dialog * pdialog) override;

      ::e_status _allocate_Display_and_connection() override;

      virtual void _on_gtk_init();


      ::wl_display * get_wayland_display() override;


   };


} // namespace node_gtk



