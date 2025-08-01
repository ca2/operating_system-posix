//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


// #ifdef G_OS_UNIX
// #include <gio/gdesktopappinfo.h>
// #endif


#include "acme/prototype/collection/string_map.h"
#include "aura_posix/node.h"


namespace node_gdk
{


   class CLASS_DECL_ACME node :
      virtual public ::aura_posix::node
   {
   public:


      gpointer m_pGtkSettingsDefault;

      GdkAppLaunchContext * m_pgdkapplaunchcontext;
      //string_map < GDesktopAppInfo * > m_mapGDesktopAppInfo;
      GAction *m_pactionWallpaper;

      ::string       m_strOsUserTheme;
      ::string       m_strOsUserIconTheme;

      ::task_pointer       m_ptaskOsUserTheme;
      ::task_pointer       m_ptaskOsUserIconTheme;


      bool  m_bGInitialized;
bool m_bFetchingDarkMode;


      node();
      ~node() override;


      virtual void _set_os_user_theme(const ::scoped_string & strTheme);
      virtual void _apply_os_user_theme();
      virtual ::string _get_os_user_theme();


      virtual void _set_os_user_icon_theme(const ::scoped_string & strIconTheme);
      virtual void _apply_os_user_icon_theme();


      //void _fill_os_theme_colors(::os_theme_colors * pthemecolors) override;
      //virtual void _fill_os_theme_colors(::os_theme_colors * pthemecolors, const ::scoped_string & scopedstrTheme, bool bDark);
      //virtual void _set_os_theme_colors(::os_theme_colors * posthemecolors);

      //int node_init_check(int * pi, char *** ppz) override;

      void initialize_window_manager() override;

      //void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::particle * pparticle) override;

      // void fetch_user_color() override;
      //
      // string os_get_user_theme() override;
      //
      // virtual string _os_get_user_theme();

      void on_start_system() override;

      //void on_system_main() override;

      bool is_branch_current() const override;

      virtual void _fetch_dark_mode();

      // bool dark_mode() const override;
      //
      // void set_dark_mode(bool bDarkMode) override;
      //
      // void os_set_user_theme(const ::scoped_string & scopedstrUserTheme) override;
      //
      // virtual ::e_status _os_set_user_theme(const ::scoped_string & scopedstrUserTheme);
      //
      // virtual ::e_status _os_set_user_icon_theme(const ::scoped_string & scopedstrUserIconTheme);

      // void os_process_user_theme(string strTheme) override;
      //
      // void os_process_user_icon_theme(string strTheme) override;

      void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize) override;

      string get_file_content_type(const ::scoped_string & scopedstrPath) override;

      bool set_wallpaper(::collection::index iScreen, string strLocalImagePath, ::windowing::display * pwindowingdisplay) override;

      string get_wallpaper(::collection::index iScreen, ::windowing::display * pwindowingdisplay) override;

//      using ::aura::node::node_post;

      virtual bool windowing_message_loop_step();

      void user_post(const ::procedure & procedure) override;

      void defer_do_main_tasks() override;

      //virtual void _os_process_user_theme_color(string strTheme);

      virtual void on_user_system_quit();

      void user_post_quit() override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      int os_launch_uri(const ::scoped_string & scopedstrUri, char * pszError = NULL, int iBufferSize = 0) override;

      void shell_launch(const ::scoped_string & scopedstrAppId) override;

      void open_internet_link_in_system_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile = {}) override;

      //void _node_file_dialog(::file::file_dialog * pdialog) override;

      //void _node_folder_dialog(::file::folder_dialog * pdialog) override;

      ::e_status _allocate_Display_and_connection() override;

      virtual void _on_gtk_init();


      //::wl_display * get_wayland_display() override;


      bool defer_windowing_post(const ::procedure & procedure) override;


      ::pointer < ::input::input > create_input() override;


      void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;


      void set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType) override;

      void _set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      void _defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      bool _system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      bool _user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);


//      void * fetch_windowing_system_display() override;
//      void windowing_system_async(const ::procedure & procedure) override;
//      void windowing_system_display_error_trap_push(int i) override;
//      void windowing_system_display_error_trap_pop_ignored(int i) override;
//


   //virtual ::string _gsettings_get(const char * pszSchema, const char * pszKey);


   virtual void _g_defer_init();


   virtual void _g_defer_term();


   virtual void _g_safe_free(void * pfree);


   virtual ::e_status _gsettings_sync();


   virtual bool _gsettings_schema_exists(const ::scoped_string & scopedstrSchema);


   virtual ::string_array _gsettings_schema_keys(const ::scoped_string & scopedstrSchema);


   virtual bool _gsettings_schema_contains_key(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   virtual ::e_status _gsettings_set(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue);


   virtual ::e_status _gsettings_get(string & strValue, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   virtual ::e_status _node_enable_wallpaper_change_notification(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   virtual ::string _g_get_file_icon_path(const char * pszPath, int iSize);


   virtual ::string _g_get_file_content_type(const char * pszPath);


   virtual bool _g_defer_get_default_theme_icon(::string & strIconPath, GIcon * picon, int iSize);

   void _g_idle_add_windowing_message_loop();

   virtual void _gdk_branch(const ::procedure & procedure);


   virtual int _gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize);



};


} // namespace node_gdk



