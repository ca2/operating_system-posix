//
// Created by camilo on 09/12/2021 15:06 BRT <3ThomasBorregaardSorensen!!
//


namespace node_gtk
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


   void g_defer_init();


   void g_defer_term();


   void g_safe_free(void * pfree);


   ::e_status gsettings_sync();


   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue);


   ::e_status gsettings_get(string & strValue, const ::string & strSchema, const ::string & strKey);


   ::e_status node_enable_wallpaper_change_notification(::node_gtk::node * pnode, const ::string & strSchema, const ::string & strKey);


   const char * g_get_file_icon_path(const char * pszPath, int iSize);


   const char * g_get_file_content_type(const char * pszPath);


   void gdk_branch(const ::procedure & procedure);


   int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize);


} // namespace node_gtk



