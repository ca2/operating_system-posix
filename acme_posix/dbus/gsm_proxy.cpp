//
// Created by camilo on 6/26/21 12?31 BRT <3ThomasBorregaardSørensen__!!
//
#include <glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include "acme/primitive/string/string.h"

#define GSM_SERVICE_DBUS   "org.gnome.SessionManager"
#define GSM_PATH_DBUS      "/org/gnome/SessionManager"
#define GSM_INTERFACE_DBUS "org.gnome.SessionManager"


static void
display_error (const char *message)
{
   g_printerr ("%s\n", message);
}



static DBusGConnection *
get_session_bus (void)
{
   DBusGConnection *bus;
   GError *error = NULL;

   bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);

   if (bus == NULL) {
      g_warning ("Couldn't connect to session bus: %s", error->message);
      g_error_free (error);
   }

   return bus;
}

static DBusGProxy *
get_sm_proxy (void)
{
   DBusGConnection *connection;
   DBusGProxy      *sm_proxy;

   connection = get_session_bus ();
   if (connection == NULL) {
      display_error (_("Could not connect to the session manager"));
      return NULL;
   }

   sm_proxy = dbus_g_proxy_new_for_name (connection,
                                         GSM_SERVICE_DBUS,
                                         GSM_PATH_DBUS,
                                         GSM_INTERFACE_DBUS);

   if (sm_proxy == NULL) {
      display_error (_("Could not connect to the session manager"));
      return NULL;
   }

   return sm_proxy;
}



void dbus_do_power_off (const char *action)
{
   DBusGProxy *sm_proxy;
   GError     *error;
   gboolean    res;

   sm_proxy = get_sm_proxy ();
   if (sm_proxy == NULL) {
      return;
   }

   error = NULL;
   res = dbus_g_proxy_call (sm_proxy,
                            action,
                            &error,
                            G_TYPE_INVALID,
                            G_TYPE_INVALID);

   if (!res) {
      if (error != NULL) {
         g_warning ("Failed to call %s: %s",
                    action, error->message);
         g_error_free (error);
      } else {
         g_warning ("Failed to call %s", action);
      }
   }

   g_clear_object (&sm_proxy);
}
