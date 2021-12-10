//
// Created by camilo on 09/12/2021. 13:03 BRT <ThomasBoregaardSorensen!!



namespace node_gtk
{

//
//   bool g_bGInitialized = false;
//
//   pthread_mutex_t g_mutexG;
//
//
//   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue)
//   {
//
//      if (strSchema.is_empty())
//      {
//
//         return error_invalid_argument;
//
//      }
//
//      if (strKey.is_empty())
//      {
//
//         return error_invalid_argument;
//
//      }
//
//      GSettings * settings = g_settings_new(strSchema);
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
//   bool gsettings_sync()
//   {
//
//      g_settings_sync();
//
//      return true;
//
//   }
//
//
//
//   namespace node_gtk
//   {


      ::boolean g_bitLastDarkMode;

      char *gsettings_get_malloc(const char *pszSchema, const char *pszKey);

      CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);

      bool gsettings_get(string &str, const char *pszSchema, const char *pszKey)
      {

         char *psz = gsettings_get_malloc(pszSchema, pszKey);

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


      bool gsettings_set(const char *pszSchema, const char *pszKey, const char *pszValue)
      {

         if (pszSchema == nullptr)
         {

            return false;

         }

         if (pszKey == nullptr)
         {

            return false;

         }

         if (pszValue == nullptr)
         {

            return false;

         }

         if (!::os_defer_init_gtk())
         {

            return false;

         }

         GSettings *settings = g_settings_new(pszSchema);

         if (settings == nullptr)
         {

            return false;

         }

         gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);

         if (settings != nullptr)
         {

            g_object_unref(settings);

         }

         return bOk;

      }


      bool gsettings_sync()
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


      char *gsettings_get_malloc(const char *pszSchema, const char *pszKey)
      {

         if (pszSchema == nullptr)
         {

            return nullptr;

         }

         if (pszKey == nullptr)
         {

            return nullptr;

         }

         if (!os_defer_init_gtk())
         {

            return nullptr;

         }

         GSettings *settings = g_settings_new(pszSchema);

         if (settings == nullptr)
         {

            return nullptr;

         }

         gchar *pgchar = g_settings_get_string(settings, pszKey);

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


      void wallpaper_change_notification(GSettings *settings, const gchar *key, gpointer data)
      {


         ::node_gtk::node * pnode = (::node_gtk::node *) data;

         pnode->m_psystem->m_papexsystem->signal(id_wallpaper_change);

      }


      GAction *g_pactionWallpaper = nullptr;


      bool g_enable_wallpaper_change_notification(const char *pszSchema, const char *pszKey)
      {

         if (!g_bGInitialized)
         {

            return false;

         }

         pmutex_lock lock(&g_mutexG);

         if (g_pactionWallpaper != nullptr)
         {

            return true;

         }

         GSettings *settings = g_settings_new(pszSchema);

         if (settings == nullptr)
         {

            return false;

         }

         g_pactionWallpaper = g_settings_create_action(settings, pszKey);

         g_object_unref(settings);

         g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), nullptr);

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


} // namespace node_gtk



