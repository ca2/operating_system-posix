//
// Created by camilo on 2026-07-15 01:36 <3ThomasBorregaardSorensen!! Mummi!! Bilbo
//
#include "framework.h"


bool gtk3_is_session_dbus_available()
{
   GError *error = NULL;
   GDBusConnection *connection =
       g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);

   if (connection != NULL)
   {
      g_object_unref(connection);
      return true;
   }

   if (error != NULL)
   {
      g_printerr("Failed to connect to session bus: %s\n", error->message);
      g_error_free(error);
   }

   return false;
}
