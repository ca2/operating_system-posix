//
// Created by camilo on 09/12/2021 15:06 BRT <3ThomasBorregaardSorensen!!
//
#pragma once


namespace gdk
{


   char * gsettings_get_malloc(const_char_pointer  pszSchema, const_char_pointer  pszKey);


   void g_defer_init();


   void g_defer_term();


   void g_safe_free(void * pfree);


   ::e_status gsettings_sync();

   
   bool gsettings_schema_exists(const ::scoped_string & scopedstrSchema);


   ::string_array gsettings_schema_keys(const ::scoped_string & scopedstrSchema);


   bool gsettings_schema_contains_key(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   ::e_status gsettings_set(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue);


   ::e_status gsettings_get(string & strValue, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   ::e_status node_enable_wallpaper_change_notification(::g::acme::windowing::display * pdisplay, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   const_char_pointer  g_get_file_icon_path(const_char_pointer  pszPath, int iSize);


   const_char_pointer  g_get_file_content_type(const_char_pointer  pszPath);


   void gdk_branch(const ::procedure & procedure);


   int gdk_launch_uri(const_char_pointer  pszUri, char * pszError, int iBufferSize);


} // namespace gdk



CLASS_DECL_ACME_WINDOWING_G ::e_status xfce4_set_wallpaper(const_char_pointer  wallpaper_path);
CLASS_DECL_ACME_WINDOWING_G ::string xfce4_get_user_theme();
CLASS_DECL_ACME_WINDOWING_G ::e_status xfce4_set_user_theme(const ::scoped_string & scopedstrTheme);




