//
// Created by camilo on 09/12/2021. 13:03 BRT <ThomasBoregaardSorensen!!
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "apex/platform/system.h"

#include <gdk/gdkwayland.h>

//::particle * user_synchronization();


namespace node_gtk3
{


//   ::logic::boolean g_bitLastDarkMode;
//
//
//   char *gsettings_get_malloc(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);
//
//
//   //CLASS_DECL_ACME void _os_process_user_theme_color(const ::scoped_string & scopedstrTheme);
//
//   ::string_array gsettings_schema_keys(const ::scoped_string & scopedstrSchema)
//   {
//
//      GSettingsSchema * pschema = g_settings_schema_source_lookup (
//         g_settings_schema_source_get_default(),
//         strSchema, FALSE);
//
//      if (::is_null(pschema))
//      {
//
//         return {};
//
//      }
//
//      auto ppchar = g_settings_schema_list_keys (pschema);
//
//      if(::is_null(ppchar))
//      {
//
//         g_settings_schema_unref (pschema);
//
//         return {};
//
//      }
//
//      ::string_array stra;
//
//      auto pp = ppchar;
//
//      while(*pp)
//      {
//
//         stra.add(*pp);
//
//         g_free(*pp);
//
//         pp++;
//
//      }
//
//      g_free(ppchar);
//
//      g_settings_schema_unref (pschema);
//
//      return ::transfer(stra);
//
//   }
//
//
//   bool gsettings_schema_contains_key(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
//   {
//
//      auto stra = gsettings_schema_keys(strSchema);
//
//      return stra.contains(strKey);
//
//   }
//
//
//   bool gsettings_schema_exists(const ::scoped_string & scopedstrSchema)
//   {
//
//      GSettingsSchema * pschema = g_settings_schema_source_lookup (
//         g_settings_schema_source_get_default(),
//         strSchema, FALSE);
//
//      if (::is_null(pschema))
//      {
//
//         return false;
//
//      }
//
//      g_settings_schema_unref (pschema);
//
//      return true;
//
//   }
//
//
//   ::e_status gsettings_get(string &str, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
//   {
//
//      char *psz = gsettings_get_malloc(strSchema, strKey);
//
//      if (scopedstr == nullptr)
//      {
//
//         return ::error_failed;
//
//      }
//
//      try
//      {
//
//         str = psz;
//
//      }
//      catch (...)
//      {
//
//      }
//
//      try
//      {
//
//         ::free(scopedstr);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      return ::success;
//
//   }
//
//
//   bool g_bGInitialized = false;
//
//
//   pthread_mutex_t g_mutexG;
//
//
//   ::e_status gsettings_set(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue)
//   {
//
//      if (strSchema.is_empty())
//      {
//
//         return error_bad_argument;
//
//      }
//
//      if (strKey.is_empty())
//      {
//
//         return error_bad_argument;
//
//      }
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return ::error_failed;
////
////      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      gboolean bOk = g_settings_set_string(settings, strKey, strValue);
//
//      g_object_unref(settings);
//
//      if(!bOk)
//      {
//
//         return error_failed;
//
//      }
//
//      return ::success;
//
//   }
//
//
//   ::e_status gsettings_sync()
//   {
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return ::error_failed;
////
////      }
//
//      ::g_settings_sync();
//
//      return ::success;
//
//   }
//
//
//   char * gsettings_get_malloc(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
//   {
//
//      if (strSchema.is_empty())
//      {
//
//         return nullptr;
//
//      }
//
//      if (strKey.is_empty())
//      {
//
//         return nullptr;
//
//      }
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return nullptr;
////
////      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      gchar *pgchar = g_settings_get_string(settings, strKey);
//
//      if (pgchar == nullptr)
//      {
//
//         g_object_unref(settings);
//
//         return nullptr;
//
//      }
//
//      char *psz = strdup(pgchar);
//
//      g_free(pgchar);
//
//      g_object_unref(settings);
//
//      return psz;
//
//   }
//
//
//   void wallpaper_change_notification(GSettings *settings, const gchar *pszKey, gpointer pdata)
//   {
//
//      ::node_gtk3::node * pnode = (::node_gtk3::node *) pdata;
//
//      pnode->system()->signal(id_wallpaper_change);
//
//   }
//
//
//   GAction *g_pactionWallpaper = nullptr;
//
//
//   ::e_status node_enable_wallpaper_change_notification(::node_gtk3::node * pnode, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
//   {
//
//      if (!g_bGInitialized)
//      {
//
//         return error_not_initialized;
//
//      }
//
//      pmutex_lock lock(&g_mutexG);
//
//      if (g_pactionWallpaper != nullptr)
//      {
//
//         return ::success;
//
//      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      g_pactionWallpaper = g_settings_create_action(settings, strKey);
//
//      g_object_unref(settings);
//
//      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), pnode);
//
//      return ::success;
//
//   }
//
//
//   void g_defer_init()
//   {
//
//      if (g_bGInitialized)
//      {
//
//         return;
//
//      }
//
//      g_bGInitialized = true;
//
//      pthread_mutex_init(&g_mutexG, nullptr);
//
//   }
//
//
//   void g_defer_term()
//   {
//
//      if (!g_bGInitialized)
//      {
//
//         return;
//
//      }
//
//      g_bGInitialized = false;
//
//      if (g_pactionWallpaper != nullptr)
//      {
//
//         g_object_unref(g_pactionWallpaper);
//
//         g_pactionWallpaper = nullptr;
//
//      }
//
//      pthread_mutex_destroy(&g_mutexG);
//
//   }
//
//
//   const_char_pointer g_get_file_icon_path(const_char_pointer pszPath, int iSize)
//   {
//
//      GFile * pfile = g_file_new_for_path (scopedstrPath);
//
//      if(pfile == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GError * perror = nullptr;
//
//      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//      if(pfileinfo == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      /* you'd have to use g_loadable_icon_load to get the actual icon */
//      GIcon * picon = g_file_info_get_icon (pfileinfo);
//
//      if(picon == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if(G_IS_FILE_ICON(G_OBJECT(picon)))
//      {
//
//         GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));
//
//         if(pfileicon == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         GFile * pfileIcon = g_file_icon_get_file(pfileicon);
//
//         if(pfileIcon == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         char * psz = strdup(g_file_get_path(pfileIcon));
//
//         return psz;
//
//      }
//      else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
//      {
//
//         GtkIconInfo *pGtkIconInfo;
//
//         GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();
//
//         if(pGtkIconTheme == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);
//
//         if(pGtkIconInfo == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         const_char_pointer point = gtk_icon_info_get_filename(pGtkIconInfo);
//
//         char * psz = nullptr;
//
//         if(point != nullptr)
//         {
//
//            psz = strdup(point);
//
//         }
//
//         return psz;
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   const_char_pointer g_get_file_content_type(const_char_pointer pszPath)
//   {
//
//      GFile * pfile = g_file_new_for_path (scopedstrPath);
//
//      if(pfile == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GError * perror = nullptr;
//
//      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//      if(pfileinfo == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      const_char_pointer pszContentType = g_file_info_get_content_type (pfileinfo);
//
//      const_char_pointer point = nullptr;
//
//      if(scopedstrContentType != nullptr)
//      {
//
//         point = strdup(scopedstrContentType);
//
//      }
//
//      return point;
//
//   }
//
//
//
//   int gdk_launch_uri(const_char_pointer pszUri, char * pszError, int iBufferSize)
//   {
//
//      gboolean ret;
//
//      GError * error = nullptr;
//
//      //g_type_init();
//
//      ret = g_app_info_launch_default_for_uri(scopedstrUri, nullptr, &error);
//
//      if(ret)
//      {
//
//         return true;
//
//      }
//
//      if(scopedstrError != nullptr)
//      {
//
//         strncpy(scopedstrError, error->message, iBufferSize);
//
//      }
//
//      return 0;
//
//   }
//
//
//   gboolean gdk_callback_run_runnable(gpointer pdata)
//   {
//
//      auto pparticle = (::subparticle *) pdata;
//
//      try
//      {
//
//         pparticle->run();
//
//      }
//      catch(...)
//      {
//
//      }
//
//      ::release(pparticle);
//
//      return FALSE;
//
//   }
//
//
//   void gdk_branch(const ::procedure & procedure)
//   {
//
//      ::subparticle * pbase = procedure.m_pbase;
//
//      ::increment_reference_count(pbase);
//
//      //synchronous_lock synchronouslock (user_synchronization());
//
//      auto psource = g_idle_source_new();
//
//      g_source_set_priority(psource, G_PRIORITY_DEFAULT);
//
//      g_source_set_callback(psource, &gdk_callback_run_runnable, pbase, nullptr);
//
//      g_source_attach(psource, g_main_context_default());
//
//   }


//   void g_safe_free(void * pfree)
//   {
//
//      if(pfree == nullptr)
//      {
//
//         return;
//
//      }
//
//      ::g_free(pfree);
//
//   }


} // namespace node_gtk3







