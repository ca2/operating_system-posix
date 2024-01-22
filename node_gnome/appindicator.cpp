//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/platform/system.h"
//#include "apex/user/user/notify_icon_bridge.h"
//int uname(struct utsname *buf);
//#ifndef RASPBERRYPIOS
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
//#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#include "acme/platform/application_menu_callback.h"
#include "apex/platform/application_menu.h"
#if defined(FREEBSD) || defined(FEDORA_LINUX)
#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#else
#include <libayatana-appindicator/app-indicator.h>
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


   static void gtk_menu_item_application_menu_callback(GtkMenuItem * pgtkmenuitem, gpointer data)
   {

      auto pcallback = (::application_menu_callback *) data;

      pcallback->on_application_menu_action(gtk_widget_get_name(GTK_WIDGET(pgtkmenuitem)));

   }


} // extern "C"



GtkMenu * gtk_menu_from_application_menu(application_menu * papplicationmenu, application_menu_callback * pcallback)
{

   int iCount = papplicationmenu->get_count();

   if(iCount <= 0)
   {

      return nullptr;

   }

   GtkWidget * pgtkwidgetMenu = gtk_menu_new();

   for(int i = 0; i < iCount; i++)
   {

      auto pitem = papplicationmenu->element_at(i);

      auto strName = pitem->m_strName;
      //const char * pszLabel = pbridge->_get_notification_area_action_label(i);
      //const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(i);
      //const char * pszDescription = pbridge->_get_notification_area_action_description(i);

      GtkWidget * pgtkwidget = nullptr;

      if(pitem->is_separator())
      {

         pgtkwidget = gtk_separator_menu_item_new();

      }
      else
      {

         pgtkwidget = gtk_menu_item_new_with_label(strName);

         if (pitem->is_popup())
         {

            auto pgtkwidgetSubMenu = gtk_menu_from_application_menu(pitem, pcallback);

            gtk_menu_item_set_submenu(GTK_MENU_ITEM(pgtkwidget), GTK_WIDGET(pgtkwidgetSubMenu));

         }
         else
         {

            auto strId = pitem->m_atom.as_string();
            auto strAccelerator = pitem->m_strAccelerator;
            auto strDescription = pitem->m_strDescription;


            gtk_widget_set_name(GTK_WIDGET(pgtkwidget), strId);

            g_signal_connect (G_OBJECT(pgtkwidget), "activate", G_CALLBACK(gtk_menu_item_application_menu_callback),
                              pcallback);

            // gtkactionentriea[iEntry].stock_id = g_strdup(pszId);

            // gtkactionentriea[iEntry].label = g_strdup(pszName);

            // //gtkactionentriea[iEntry].accelerator = g_strdup(pszAccelerator);

            // //gtkactionentriea[iEntry].accelerator = nullptr;

            // gtkactionentriea[iEntry].accelerator = g_strdup("");

            // gtkactionentriea[iEntry].tooltip = g_strdup(pszDescription);

            // gtkactionentriea[iEntry].callback = G_CALLBACK (user_notify_icon_bridge_extra_action);

            // iEntry++;

         }

      }

      gtk_widget_show (pgtkwidget);

      gtk_menu_shell_append (GTK_MENU_SHELL (pgtkwidgetMenu), pgtkwidget);

      //gtk_container_add (GTK_CONTAINER (pgtkwidgetMenu), pgtkwidget);

   }

   return GTK_MENU(pgtkwidgetMenu);


}


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


   bool appindicator::create(const char * pszId, const char * pszIcon, const char * pszFolder, application_menu * papplicationmenu, application_menu_callback * pcallback)
   {

      ::pointer < ::node_gtk::node > pgtknode = acmenode();

      if (!::node_gtk::os_defer_init_gtk(pgtknode))
      {

         return false;

      }

      m_pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

      if(m_pindicator == nullptr)
      {

         return false;

      }

      if(!init(papplicationmenu, pcallback))
      {

         close();

         return false;

      }

      return true;

   }




   bool appindicator::init(application_menu * papplicationmenu, application_menu_callback * pcallback)
   {
//
//      int iCount = pbridge->_get_notification_area_action_count();
//
//      if(iCount <= 0)
//      {
//
//         return false;
//
//      }

      auto pgtkmenu = gtk_menu_from_application_menu(papplicationmenu, pcallback);

//      for(int i = 0; i < iCount; i++)
//      {
//
//         const char * pszName = pbridge->_get_notification_area_action_name(i);
//         const char * pszId = pbridge->_get_notification_area_action_id(i);
//         const char * pszLabel = pbridge->_get_notification_area_action_label(i);
//         const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(i);
//         const char * pszDescription = pbridge->_get_notification_area_action_description(i);
//
//         GtkWidget * pgtkwidget = nullptr;
//
//         if(ansi_icmp(pszName, "separator") == 0)
//         {
//
//   	      pgtkwidget = gtk_separator_menu_item_new();
//
//         }
//         else
//         {
//
//            pgtkwidget = gtk_menu_item_new_with_label(pszLabel);
//
//            gtk_widget_set_name(GTK_WIDGET(pgtkwidget), pszId);
//
//            g_signal_connect (G_OBJECT(pgtkwidget), "activate", G_CALLBACK (user_notify_icon_bridge_extra_action), pbridge);
//
//            // gtkactionentriea[iEntry].stock_id = g_strdup(pszId);
//
//            // gtkactionentriea[iEntry].label = g_strdup(pszName);
//
//            // //gtkactionentriea[iEntry].accelerator = g_strdup(pszAccelerator);
//
//            // //gtkactionentriea[iEntry].accelerator = nullptr;
//
//            // gtkactionentriea[iEntry].accelerator = g_strdup("");
//
//            // gtkactionentriea[iEntry].tooltip = g_strdup(pszDescription);
//
//            // gtkactionentriea[iEntry].callback = G_CALLBACK (user_notify_icon_bridge_extra_action);
//
//            // iEntry++;
//
//         }
//
//         gtk_widget_show (pgtkwidget);
//
//         gtk_menu_shell_append (GTK_MENU_SHELL (pgtkwidgetMenu), pgtkwidget);
//
//  	      //gtk_container_add (GTK_CONTAINER (pgtkwidgetMenu), pgtkwidget);
//
//      }

      informationf("appindicator::init GtkMenu = %" PRI0xPTR, (long unsigned int) pgtkmenu);

      app_indicator_set_menu(m_pindicator, pgtkmenu);

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

      user_post([pindicator]()
               {

                  app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

               });

      m_pindicator = NULL;

   }


} // namespace node_gnome



