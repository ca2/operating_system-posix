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
      virtual public ::node_gtk::node
   {
   public:


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

      virtual bool os_set_user_theme(const string & strUserTheme) override;

      virtual void os_process_user_theme(string strTheme) override;

      virtual void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::string & strPath, int iSize) override;

      string get_file_content_type(const ::string & strPath) override;

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      virtual string get_wallpaper(index iScreen) override;

      virtual bool windowing_message_loop_step();

      virtual void _os_process_user_theme_color(string strTheme);

      bool should_launch_on_node(::subject * psubject) override;

      bool launch_on_node(::subject * psubject) override;

      int os_launch_uri(const ::string & strUri, char * pszError = nullptr, int iBufferSize = 0) override;

      void handle(::subject * psubject, ::context * pcontext) override;


   };


} // namespace node_gnome




