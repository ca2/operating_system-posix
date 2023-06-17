//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#include "framework.h"
#include "acme/platform/system.h"
#include "apex/user/notify_icon_bridge.h"
//int uname(struct utsname *buf);
//#ifndef RASPBERRYPIOS
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
//#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#ifdef AYATANA_APPINDICATOR
#include <libayatana-appindicator/app-indicator.h>
#else
#include <libappindicator/app-indicator.h>
#endif
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#else // MANJARO
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#endif
//#endif



#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//void g_safe_free(void * pfree);
//{
//
//   if(pfree == nullptr)
//   {
//
//      return;
//
//   }
//
//   ::g_free(pfree);
//
//}

#include "aura_posix/user_notify_icon_bridge.h"


extern "C"
{


   static void user_notify_icon_bridge_extra_action(GtkMenuItem * pgtkmenuitem, gpointer data)
   {

      auto pbridge = (::user_notify_icon_bridge *) data;

      pbridge->call_notification_area_action(gtk_widget_get_name(GTK_WIDGET(pgtkmenuitem)));

   }


} // extern "C"


#include "appindicator.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"


namespace node_gnome
{


   appindicator::appindicator()
   {

      m_pindicator = nullptr;

   }


   appindicator::~appindicator()
   {

   }


   bool appindicator::create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
   {

      if (!::node_gtk::os_defer_init_gtk(acmesystem()))
      {

         return false;

      }

      m_pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

      if(m_pindicator == nullptr)
      {

         return false;

      }

      if(!init(pbridge))
      {

         close();

         return false;

      }

      return true;

   }


   bool appindicator::init(user_notify_icon_bridge * pbridge)
   {

      int iCount = pbridge->_get_notification_area_action_count();

      if(iCount <= 0)
      {

         return false;

      }

      GtkWidget * pgtkwidgetMenu = gtk_menu_new();

      for(int i = 0; i < iCount; i++)
      {

         const char * pszName = pbridge->_get_notification_area_action_name(i);
         const char * pszId = pbridge->_get_notification_area_action_id(i);
         const char * pszLabel = pbridge->_get_notification_area_action_label(i);
         const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(i);
         const char * pszDescription = pbridge->_get_notification_area_action_description(i);

         GtkWidget * pgtkwidget = nullptr;

         if(strcasecmp(pszName, "separator") == 0)
         {

   	      pgtkwidget = gtk_separator_menu_item_new();

         }
         else
         {

            pgtkwidget = gtk_menu_item_new_with_label(pszLabel);

            gtk_widget_set_name(GTK_WIDGET(pgtkwidget), pszId);

            g_signal_connect (G_OBJECT(pgtkwidget), "activate", G_CALLBACK (user_notify_icon_bridge_extra_action), pbridge);

            // gtkactionentriea[iEntry].stock_id = g_strdup(pszId);

            // gtkactionentriea[iEntry].label = g_strdup(pszName);

            // //gtkactionentriea[iEntry].accelerator = g_strdup(pszAccelerator);

            // //gtkactionentriea[iEntry].accelerator = nullptr;

            // gtkactionentriea[iEntry].accelerator = g_strdup("");

            // gtkactionentriea[iEntry].tooltip = g_strdup(pszDescription);

            // gtkactionentriea[iEntry].callback = G_CALLBACK (user_notify_icon_bridge_extra_action);

            // iEntry++;

         }

         gtk_widget_show (pgtkwidget);
   		
         gtk_menu_shell_append (GTK_MENU_SHELL (pgtkwidgetMenu), pgtkwidget);

  	      //gtk_container_add (GTK_CONTAINER (pgtkwidgetMenu), pgtkwidget);

      }

      printf("appindicator::init GtkMenu = %" PRI0xPTR, (long unsigned int) pgtkwidgetMenu);

      app_indicator_set_menu(m_pindicator, GTK_MENU(pgtkwidgetMenu));

      app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_ACTIVE);

      return true;

   }


   void appindicator::close()
   {


      if(m_pindicator == NULL)
      {

         return;

      }

      auto pindicator = m_pindicator;

      acmesystem()->windowing_post([pindicator]()
               {

                  app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

               });

      m_pindicator = NULL;

   }


} // namespace node_gnome



