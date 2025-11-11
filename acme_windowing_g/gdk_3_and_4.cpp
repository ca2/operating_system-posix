//
// Created by camilo on 09/12/2021. 13:03 BRT <ThomasBoregaardSorensen!!
#include "framework.h"
#include "gdk_3_and_4.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/prototype/logic/boolean.h"
#include "acme/platform/system.h"
#include <dbus/dbus.h>
#include "display.h"

namespace gdk
{


   ::logic::boolean g_bitLastDarkMode;


   char *gsettings_get_malloc(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey);


   //CLASS_DECL_ACME void _os_process_user_theme_color(const ::scoped_string & scopedstrTheme);

   ::string_array_base gsettings_schema_keys(const ::scoped_string & scopedstrSchema)
   {

      GSettingsSchema * pschema = g_settings_schema_source_lookup (
         g_settings_schema_source_get_default(), 
         scopedstrSchema, FALSE);
  
      if (::is_null(pschema))
      {

         return {};

      }

      auto ppchar = g_settings_schema_list_keys (pschema);

      if(::is_null(ppchar))
      {

         g_settings_schema_unref (pschema);

         return {};

      }

      ::string_array_base stra;

      auto pp = ppchar;

      while(*pp)
      {

         stra.add(*pp);

         g_free(*pp);

         pp++;

      }

      g_free(ppchar);

      g_settings_schema_unref (pschema);
  
      return ::transfer(stra);

   }


   bool gsettings_schema_contains_key(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
   {

      auto stra = gsettings_schema_keys(scopedstrSchema);

      return stra.contains(scopedstrKey);

   }


   bool gsettings_schema_exists(const ::scoped_string & scopedstrSchema)
   { 
  
      GSettingsSchema * pschema = g_settings_schema_source_lookup (
         g_settings_schema_source_get_default(), 
         scopedstrSchema, FALSE);
  
      if (::is_null(pschema))
      {

         return false;

      }

      g_settings_schema_unref (pschema);
  
      return true;

   }


   ::e_status gsettings_get(string &str, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
   {

      char *psz = gsettings_get_malloc(scopedstrSchema, scopedstrKey);

      if (::is_null(psz))
      {

         return ::error_failed;

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

      return ::success;

   }


   bool g_bGInitialized = false;


   pthread_mutex_t g_mutexG;


   ::e_status gsettings_set(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue)
   {

      if (scopedstrSchema.is_empty())
      {

         return error_bad_argument;

      }

      if (scopedstrKey.is_empty())
      {

         return error_bad_argument;

      }

      //::pointer < ::windowing_gtk4::windowing > pgtk4windowing = ::platform::get()->system()->session()->user()->windowing();

      // if (!pgtk4windowing->os_deos_defer_init_gtk())
      // {
      //
      //    return ::error_failed;
      //
      // }

      GSettings *settings = g_settings_new(scopedstrSchema);

      if (settings == nullptr)
      {

         return error_failed;

      }

      gboolean bOk = g_settings_set_string(settings, scopedstrKey, scopedstrValue);

      g_object_unref(settings);

      if(!bOk)
      {

         return error_failed;

      }

      return ::success;

   }


   ::e_status gsettings_sync()
   {

//;;      ::pointer < ::node_gtk4::node > pgtknode = ::platform::get()->system()->node();

      // if (!os_defer_init_gtk(pgtknode))
      // {
      //
      //    return ::error_failed;
      //
      // }

      ::g_settings_sync();

      return ::success;

   }


   char * gsettings_get_malloc(const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
   {

      if (scopedstrSchema.is_empty())
      {

         return nullptr;

      }

      if (scopedstrKey.is_empty())
      {

         return nullptr;

      }

      // ::pointer < ::node_gtk4::node > pgtknode = ::platform::get()->system()->node();
      //
      // if (!os_defer_init_gtk(pgtknode))
      // {
      //
      //    return nullptr;
      //
      // }

      GSettings *settings = g_settings_new(scopedstrSchema);

      if (settings == nullptr)
      {

         return nullptr;

      }

      gchar *pgchar = g_settings_get_string(settings, scopedstrKey);

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

      ::g::acme::windowing::display * pdisplay = (::g::acme::windowing::display *) pdata;

      pdisplay->_on_wallpaper_change();

   }


   GAction *g_pactionWallpaper = nullptr;


   ::e_status node_enable_wallpaper_change_notification(::g::acme::windowing::display * pdisplay, const ::scoped_string & scopedstrSchema, const ::scoped_string & scopedstrKey)
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

      GSettings *settings = g_settings_new(scopedstrSchema);

      if (settings == nullptr)
      {

         return error_failed;

      }

      g_pactionWallpaper = g_settings_create_action(settings, scopedstrKey);

      g_object_unref(settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), pdisplay);

      return ::success;

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


   const_char_pointer g_get_file_icon_path(const_char_pointer pszPath, int iSize)
   {

      GFile * pfile = g_file_new_for_path (pszPath);

      if(pfile == nullptr)
      {

         return nullptr;

      }

      GError * pgerror = nullptr;

      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &pgerror);

      if(pfileinfo == nullptr)
      {
         if (pgerror)
         {
            g_clear_error(&pgerror);
         }

         return nullptr;

      }
      if (pgerror)
      {
         g_clear_error(&pgerror);
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

#if HAS_GTK4

      else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
      {

         GtkIconPaintable *pGtkIconPaintable;

         auto pgdkdisplay = gdk_display_get_default();

         GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_for_display(pgdkdisplay);

         if(pGtkIconTheme == nullptr)
         {

            return nullptr;

         }

         pGtkIconPaintable = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon, iSize, 1, GTK_TEXT_DIR_NONE, (GtkIconLookupFlags) 0);

         if(pGtkIconPaintable == nullptr)
         {

            return nullptr;

         }

         auto pgfile = gtk_icon_paintable_get_file(pGtkIconPaintable);

         char * psz = nullptr;

         if(pgfile != nullptr)
         {

            auto path = g_file_get_path(pgfile);

            if(path)
            {

               psz = strdup(path);

            }

         }

         return psz;

      }

#endif

      return nullptr;

   }


   const_char_pointer g_get_file_content_type(const_char_pointer pszPath)
   {

      GFile * pfile = g_file_new_for_path (pszPath);

      if(pfile == nullptr)
      {

         return nullptr;

      }

      GError * pgerror = nullptr;

      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &pgerror);

      if(pfileinfo == nullptr)
      {

         if (pgerror)
         {
            g_clear_error(&pgerror);
         }


         return nullptr;

      }

      if (pgerror)
      {
         g_clear_error(&pgerror);
      }


      const_char_pointer pszContentType = g_file_info_get_content_type (pfileinfo);

      const_char_pointer p = nullptr;

      if(pszContentType != nullptr)
      {

         p = strdup(pszContentType);

      }

      return p;

   }



   int gdk_launch_uri(const_char_pointer pszUri, char * pszError, int iBufferSize)
   {

      gboolean ret;

      GError * pgerror = nullptr;

      //g_type_init();

      ret = g_app_info_launch_default_for_uri(pszUri, nullptr, &pgerror);

      if(ret)
      {

         if (pgerror)
         {
            if(::is_set(pszError))
            {

               strncpy(pszError, pgerror->message, iBufferSize);

            }
            g_clear_error(&pgerror);
         }


         return true;

      }

      if (pgerror)
      {
         if(::is_set(pszError))
         {

            strncpy(pszError, pgerror->message, iBufferSize);

         }
         g_clear_error(&pgerror);
      }

      return 0;

   }


   gboolean gdk_callback_run_runnable(gpointer pdata)
   {

      auto pparticle = (::subparticle *) pdata;

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

      ::subparticle * pbase = procedure.m_pbase;

      ::increment_reference_count(pbase);

      //synchronous_lock synchronouslock (user_synchronization());

      auto psource = g_idle_source_new();

      g_source_set_priority(psource, G_PRIORITY_DEFAULT);

      g_source_set_callback(psource, &gdk_callback_run_runnable, pbase, nullptr);

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


} // namespace gdk


void gtk_defer_do_main_tasks()
{

   if(!::is_main_thread())
   {

      return;

   }

   for(int i = 0; i < 10 && g_main_context_pending(NULL); i++)
   {

      g_main_context_iteration(NULL, TRUE);

   }


}


::e_status dbus_set_string(const_char_pointer channel, const_char_pointer key, const_char_pointer payload)
{
    DBusError err;
    DBusConnection *conn;
    DBusMessage *msg;
    DBusMessageIter args;
    DBusPendingCall *pending;

    // Initialize the errors
    dbus_error_init(&err);

    // Connect to the session bus
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
       return error_failed;
    }
    if (!conn) {
        return error_failed;
    }

    // Create a new method call
    msg = dbus_message_new_method_call(
        "org.xfce.Xfconf",                  // Target service name
        "/org/xfce/Xfconf",                // Object path
        "org.xfce.Xfconf",                 // Interface name
        "SetProperty"                      // Method name
    );
    if (!msg) {
        fprintf(stderr, "Message Null\n");
       return error_failed;
    }

    // Append arguments
    dbus_message_iter_init_append(msg, &args);
    //const_char_pointer channel = "xfce4-desktop";
    //const_char_pointer property = "/backdrop/screen0/monitor0/workspace0/last-image";

    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &channel) ||
        !dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &key)) {
        fprintf(stderr, "Out of Memory!\n");
       return error_failed;
    }

    // Add the value to be set (variant type with a single string)
    DBusMessageIter variant;
    const_char_pointer type = "s"; // String type
    dbus_message_iter_open_container(&args, DBUS_TYPE_VARIANT, type, &variant);
    if (!dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &payload)) {
        fprintf(stderr, "Out of Memory!\n");
       return error_failed;
    }
    dbus_message_iter_close_container(&args, &variant);

    // Send the message and block until a reply
    if (!dbus_connection_send_with_reply(conn, msg, &pending, -1)) {
        fprintf(stderr, "Out of Memory!\n");
       return error_failed;
    }
    if (!pending) {
        fprintf(stderr, "Pending Call Null\n");
       return error_failed;
    }
    dbus_connection_flush(conn);

    // Free the message
    dbus_message_unref(msg);

    // Wait for the reply
    dbus_pending_call_block(pending);

    // Get the reply message
    msg = dbus_pending_call_steal_reply(pending);
    if (!msg) {
        fprintf(stderr, "Reply Null\n");
       return error_failed;
    }
    dbus_pending_call_unref(pending);

    // Free the reply
    dbus_message_unref(msg);

   return ::success;

}


::e_status dbus_get_property_string(::string & str, const_char_pointer channel, const_char_pointer property)
{

    DBusError err;
    DBusConnection *conn;
    DBusMessage *msg, *reply;
    DBusMessageIter args;
    DBusMessageIter reply_iter;
    char *value;

    // Initialize the D-Bus error
    dbus_error_init(&err);

    // Connect to the session bus
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
       return error_failed;
    }
    if (!conn) {
       return error_failed;
    }

    // Create a new method call for GetProperty
    msg = dbus_message_new_method_call(
        "org.xfce.Xfconf",                  // Target service
        "/org/xfce/Xfconf",                // Object path
        "org.xfce.Xfconf",                 // Interface
        "GetProperty"                      // Method name
    );
    if (!msg) {
        fprintf(stderr, "Message Null\n");
       return error_failed;
    }

    // Append arguments to the method call
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &channel) ||
        !dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &property)) {
        fprintf(stderr, "Out of Memory!\n");
       return error_failed;
    }

    // Send the message and wait for a reply
    reply = dbus_connection_send_with_reply_and_block(conn, msg, -1, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Error in method call (%s)\n", err.message);
        dbus_error_free(&err);
       return error_failed;
    }
    if (!reply) {
        fprintf(stderr, "Reply Null\n");
       return error_failed;
    }

    // Read the reply
    if (!dbus_message_iter_init(reply, &reply_iter)) {
        fprintf(stderr, "Reply has no arguments!\n");
       return error_failed;
    } else if (DBUS_TYPE_VARIANT != dbus_message_iter_get_arg_type(&reply_iter)) {
        fprintf(stderr, "Unexpected argument type!\n");
       return error_failed;
    } else {
        DBusMessageIter variant_iter;
        dbus_message_iter_recurse(&reply_iter, &variant_iter);
        if (DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&variant_iter)) {
            dbus_message_iter_get_basic(&variant_iter, &value);
            printf("Property Value: %s\n", value);
           str = value;
           return success;
        } else {
            fprintf(stderr, "Unexpected value type!\n");
           return error_failed;
        }
    }

    // Free the reply and message
    dbus_message_unref(reply);
    dbus_message_unref(msg);

   return success;
}


::e_status xfce4_set_wallpaper(const_char_pointer wallpaper_path)
{

   auto estatusMonitor0 = dbus_set_string("xfce4-desktop", "/backdrop/screen0/monitor0/workspace0/last-image", wallpaper_path);

   if (estatusMonitor0.succeeded())
   {

      printf("Wallpaper for monitor0 set to %s\n", wallpaper_path);

   }

   auto estatusMonitorVirtual1 = dbus_set_string("xfce4-desktop", "/backdrop/screen0/monitorVirtual1/workspace0/last-image", wallpaper_path);

   if (estatusMonitorVirtual1.succeeded())
   {

      printf("Wallpaper for monitorVirtual1 set to %s\n", wallpaper_path);

   }

   if (estatusMonitor0.failed() && estatusMonitorVirtual1.failed())
   {

      return error_failed;

   }

   return ::success;

}





CLASS_DECL_ACME_WINDOWING_G ::string xfce4_get_user_theme()
{

   ::string strThemeName;

   auto estatusSetThemeName= dbus_get_property_string(strThemeName, "xsettings", "/Net/ThemeName");

   return strThemeName;

}


CLASS_DECL_ACME_WINDOWING_G ::e_status xfce4_set_user_theme(const ::scoped_string & scopedstrTheme)
{

   ::string strThemeName;

   strThemeName = scopedstrTheme;

   auto estatusSetThemeName= dbus_set_string("xsettings", "/Net/ThemeName", strThemeName);

   return estatusSetThemeName;

}



