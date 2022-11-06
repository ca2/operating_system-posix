//
// Created by camilo on 09/12/2021. 13:03 BRT <ThomasBoregaardSorensen!!
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/system.h"


::particle * user_synchronization();


namespace node_gtk
{


   ::tristate g_bitLastDarkMode;


   char *gsettings_get_malloc(const ::string & strSchema, const ::string & strKey);


   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);


   ::e_status gsettings_get(string &str, const ::string & strSchema, const ::string & strKey)
   {

      char *psz = gsettings_get_malloc(strSchema, strKey);

      if (psz == nullptr)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch (...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch (...)
      {

      }

      return true;

   }


   bool g_bGInitialized = false;


   pthread_mutex_t g_mutexG;


   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue)
   {

      if (strSchema.is_empty())
      {

         return error_bad_argument;

      }

      if (strKey.is_empty())
      {

         return error_bad_argument;

      }

      if (!os_defer_init_gtk(::get_system()))
      {

         return false;

      }

      GSettings *settings = g_settings_new(strSchema);

      if (settings == nullptr)
      {

         return error_failed;

      }

      gboolean bOk = g_settings_set_string(settings, strKey, strValue);

      g_object_unref(settings);

      if(!bOk)
      {

         return error_failed;

      }

      return ::success;

   }


   ::e_status gsettings_sync()
   {

//         if (!os_defer_init_gtk())
//         {
//
//            return false;
//
//         }

      ::g_settings_sync();

      return true;

   }


   char * gsettings_get_malloc(const ::string & strSchema, const ::string & strKey)
   {

      if (strSchema.is_empty())
      {

         return nullptr;

      }

      if (strKey.is_empty())
      {

         return nullptr;

      }

      if (!os_defer_init_gtk(::get_system()))
      {

         return nullptr;

      }

      GSettings *settings = g_settings_new(strSchema);

      if (settings == nullptr)
      {

         return nullptr;

      }

      gchar *pgchar = g_settings_get_string(settings, strKey);

      if (pgchar == nullptr)
      {

         g_object_unref(settings);

         return nullptr;

      }

      char *psz = strdup(pgchar);

      g_free(pgchar);

      g_object_unref(settings);

      return psz;

   }


   void wallpaper_change_notification(GSettings *settings, const gchar *pszKey, gpointer pdata)
   {

      ::node_gtk::node * pnode = (::node_gtk::node *) pdata;

      pnode->acmesystem()->m_papexsystem->signal(id_wallpaper_change);

   }


   GAction *g_pactionWallpaper = nullptr;


   ::e_status node_enable_wallpaper_change_notification(::node_gtk::node * pnode, const ::string & strSchema, const ::string & strKey)
   {

      if (!g_bGInitialized)
      {

         return error_not_initialized;

      }

      pmutex_lock lock(&g_mutexG);

      if (g_pactionWallpaper != nullptr)
      {

         return ::success;

      }

      GSettings *settings = g_settings_new(strSchema);

      if (settings == nullptr)
      {

         return error_failed;

      }

      g_pactionWallpaper = g_settings_create_action(settings, strKey);

      g_object_unref(settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), pnode);

      return true;

   }


   void g_defer_init()
   {

      if (g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = true;

      pthread_mutex_init(&g_mutexG, nullptr);

   }


   void g_defer_term()
   {

      if (!g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = false;

      if (g_pactionWallpaper != nullptr)
      {

         g_object_unref(g_pactionWallpaper);

         g_pactionWallpaper = nullptr;

      }

      pthread_mutex_destroy(&g_mutexG);

   }


   const char * g_get_file_icon_path(const char * pszPath, int iSize)
   {

      GFile * pfile = g_file_new_for_path (pszPath);

      if(pfile == nullptr)
      {

         return nullptr;

      }

      GError * perror = nullptr;

      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

      if(pfileinfo == nullptr)
      {

         return nullptr;

      }

      /* you'd have to use g_loadable_icon_load to get the actual icon */
      GIcon * picon = g_file_info_get_icon (pfileinfo);

      if(picon == nullptr)
      {

         return nullptr;

      }

      if(G_IS_FILE_ICON(G_OBJECT(picon)))
      {

         GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));

         if(pfileicon == nullptr)
         {

            return nullptr;

         }

         GFile * pfileIcon = g_file_icon_get_file(pfileicon);

         if(pfileIcon == nullptr)
         {

            return nullptr;

         }

         char * psz = strdup(g_file_get_path(pfileIcon));

         return psz;

      }
      else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
      {

         GtkIconInfo *pGtkIconInfo;

         GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();

         if(pGtkIconTheme == nullptr)
         {

            return nullptr;

         }

         pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);

         if(pGtkIconInfo == nullptr)
         {

            return nullptr;

         }

         const char * point = gtk_icon_info_get_filename(pGtkIconInfo);

         char * psz = nullptr;

         if(point != nullptr)
         {

            psz = strdup(point);

         }

         return psz;

      }

      return nullptr;

   }


   const char * g_get_file_content_type(const char * pszPath)
   {

      GFile * pfile = g_file_new_for_path (pszPath);

      if(pfile == nullptr)
      {

         return nullptr;

      }

      GError * perror = nullptr;

      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

      if(pfileinfo == nullptr)
      {

         return nullptr;

      }

      const char * pszContentType = g_file_info_get_content_type (pfileinfo);

      const char * point = nullptr;

      if(pszContentType != nullptr)
      {

         point = strdup(pszContentType);

      }

      return point;

   }



   int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
   {

      gboolean ret;

      GError * error = nullptr;

      //g_type_init();

      ret = g_app_info_launch_default_for_uri(pszUri, nullptr, &error);

      if(ret)
      {

         return true;

      }

      if(pszError != nullptr)
      {

         strncpy(pszError, error->message, iBufferSize);

      }

      return 0;

   }


   gboolean gdk_callback_run_runnable(gpointer pdata)
   {

      auto pparticle = (::particle *) pdata;

      try
      {

         pparticle->run();

      }
      catch(...)
      {

      }

      ::release(pparticle);

      return FALSE;

   }


   void gdk_branch(const ::procedure & procedure)
   {

      ::particle * pparticle = procedure.m_p;

      ::increment_reference_count(pparticle);

      synchronous_lock synchronouslock (user_synchronization());

      auto psource = g_idle_source_new();

      g_source_set_priority(psource, G_PRIORITY_DEFAULT);

      g_source_set_callback(psource, &gdk_callback_run_runnable, pparticle, nullptr);

      g_source_attach(psource, g_main_context_default());

   }


   void g_safe_free(void * pfree)
   {

      if(pfree == nullptr)
      {

         return;

      }

      ::g_free(pfree);

   }


} // namespace node_gtk



