#pragma once


namespace aaa_node_gnome
{


   bool aaa_gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue);

   bool aaa_gsettings_sync();

   char * aaa_gsettings_get_malloc(const char * pszSchema, const char * pszKey);

   bool aaa_g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey);

   void aaa_g_defer_init();

   void aaa_g_defer_term();

   void aaa_os_calc_dark_mode();


} // namespace aaa_node_gnome



