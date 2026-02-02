//
// Created by camilo on 6/26/21 12?31 BRT <3ThomasBorregaardSorensen__!!
//
#include <glib.h>
#include <dbus/dbus-glib-lowlevel.h>


#define GSM_SERVICE_DBUS   "org.gnome.SessionManager"
#define GSM_PATH_DBUS      "/org/gnome/SessionManager"
#define GSM_INTERFACE_DBUS "org.gnome.SessionManager"


static void
display_error (const_char_pointer message)
{
   g_printerr ("%s\n", message);
}



static DBusGConnection *
get_session_bus (void)
{
   DBusGConnection *bus;
   GError * pgerror = NULL;

   bus = dbus_g_bus_get (DBUS_BUS_SESSION, &pgerror);

   if (bus == NULL) {
      if(pgerror)
      {
         g_warning ("Couldn't connect to session bus: %s", pgerror->message);
         g_clear_error(&pgerror);
      }
   }
         if (pgerror)
         {

            g_clear_error(&pgerror);

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
      display_error ("Could not connect to the session manager");
      return NULL;
   }

   sm_proxy = dbus_g_proxy_new_for_name (connection,
                                         GSM_SERVICE_DBUS,
                                         GSM_PATH_DBUS,
                                         GSM_INTERFACE_DBUS);

   if (sm_proxy == NULL) {
      display_error ("Could not connect to the session manager");
      return NULL;
   }

   return sm_proxy;
}



void dbus_do_power_off (const_char_pointer action)
{
   DBusGProxy *sm_proxy;
   GError * pgerror = nullptr;
   gboolean    res;

   sm_proxy = get_sm_proxy ();
   if (sm_proxy == NULL) {
      return;
   }

   error = NULL;
   res = dbus_g_proxy_call (sm_proxy,
                            action,
                            &pgerror,
                            G_TYPE_INVALID,
                            G_TYPE_INVALID);

   if (!res) {
      if (pgerror != NULL) {
         g_warning ("Failed to call %s: %s",
                    action, pgerror->message);
         g_error_free (error);
      } else {
         g_warning ("Failed to call %s", action);
      }
   }
         if (pgerror)
         {

            g_clear_error(&pgerror);

         }

   g_clear_object (&sm_proxy);
}
