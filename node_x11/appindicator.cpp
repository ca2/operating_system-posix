//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/platform/system.h"
#include "apex/message/command.h"
//#include "apex/user/user/notify_icon_bridge.h"
//int uname(struct utsname *buf);
//#ifndef RASPBERRYPIOS
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
//#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#include "acme/handler/command_handler.h"
#include "acme/platform/application_menu.h"
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

//#include "acme_windowing_g/activation_token.h"
#include "aura_posix/user_notify_icon_bridge.h"


extern "C"
{


   // static void gtk_menu_item_application_menu_callback(GtkMenuItem * pgtkmenuitem, gpointer p)
   // {
   //
   //    auto pcommandhandler = (::command_handler *) p;
   //
   //    ::atom atom;
   //
   //    atom = gtk_widget_get_name(GTK_WIDGET(pgtkmenuitem));
   //
   //    //auto pactivationtoken= øallocate ::gtk3::acme::windowing::activation_token();
   //
   //    //pcallback->on_application_menu_command(atom, puseractivationtoken);
   //
   //    pcommandhandler->handle_command(atom, nullptr);
   //
   // }


} // extern "C"

// gboolean on_menu_item_button_press(GtkWidget *widget, GdkEventButton *happening, gpointer p) {
//    if (happening->button == 1) {  // Left mouse button
//       //g_print("Left button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
//
//       auto pcommandhandler = (::command_handler *) p;
//
//       ::atom atom;
//
//       atom = gtk_widget_get_name(GTK_WIDGET(widget));
//
//       auto puseractivationtoken= øallocate ::common_gtk::activation_token(happening->time);
//
//       pcommandhandler->handle_command(atom, puseractivationtoken);
//
//       // auto *  = (::operating_system::a_system_menu_item *)p;
//       //
//       // auto pwindow = (::gtk3::acme::windowing::window *)pitem->m_pWindowingImplWindow;
//       // gtk_widget_hide(GTK_WIDGET(pwindow->m_pgtkwidgetSystemMenu));
//       //
//       // gtk_menu_popdown(GTK_MENU(pwindow->m_pgtkwidgetSystemMenu));
//       //
//       // gtk_widget_destroy(pwindow->m_pgtkwidgetSystemMenu);
//       // pwindow->_on_a_system_menu_item_button_press(pitem, widget, happening);
//       //
//       // pwindow->m_psystemmenu.release();
//       //
//       // pwindow->m_pgtkwidgetSystemMenu = nullptr;
//    } else if (happening->button == 3) {  // Right mouse button
//       //g_print("Right button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
//    }
//    return FALSE;  // Return FALSE to propagate the happening, or TRUE to stop further happening handling
// }

// GtkMenu * gtk_menu_from_application_menu(application_menu * papplicationmenu, ::command_handler * pcommandhandler)
// {
//
//    int iCount = papplicationmenu->get_count();
//
//    if(iCount <= 0)
//    {
//
//       return nullptr;
//
//    }
//
//    GtkWidget * pgtkwidgetMenu = gtk_menu_new();
//
//    gtk_widget_add_events(pgtkwidgetMenu, GDK_BUTTON_PRESS_MASK);
//
//    for(int i = 0; i < iCount; i++)
//    {
//
//       auto pitem = papplicationmenu->element_at(i);
//
//       auto strName = pitem->m_strName;
//       //const_char_pointer pszLabel = pbridge->_get_notification_area_action_label(i);
//       //const_char_pointer pszAccelerator = pbridge->_get_notification_area_action_accelerator(i);
//       //const_char_pointer pszDescription = pbridge->_get_notification_area_action_description(i);
//
//       GtkWidget * pgtkwidget = nullptr;
//
//       if(pitem->is_separator())
//       {
//
//          pgtkwidget = gtk_separator_menu_item_new();
//
//       }
//       else
//       {
//
//          pgtkwidget = gtk_menu_item_new_with_label(strName);
//
//          if (pitem->is_popup())
//          {
//
//             auto pgtkwidgetSubMenu = gtk_menu_from_application_menu(pitem, pcommandhandler);
//
//             gtk_menu_item_set_submenu(GTK_MENU_ITEM(pgtkwidget), GTK_WIDGET(pgtkwidgetSubMenu));
//
//          }
//          else
//          {
//
//             auto strId = pitem->m_atomMenu.as_string();
//             auto strAccelerator = pitem->m_strAccelerator;
//             auto strDescription = pitem->m_strDescription;
//
//
//             gtk_widget_set_name(GTK_WIDGET(pgtkwidget), strId);
//
//             // //if(pitem->m_strAtom.begins("***"))
//             // {
//             //    gtk_widget_add_events(pgtkwidget, GDK_BUTTON_PRESS_MASK);
//             //
//             //    // Connect the button-press-event signal to handle button press happenings on menu items
//             //    g_signal_connect(pgtkwidget, "button-press-event", G_CALLBACK(on_menu_item_button_press), pcommandhandler);
//             //
//             // }
//             // else {
//             //    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), pitem.m_p);
//             // }
//             g_signal_connect (G_OBJECT(pgtkwidget), "activate", G_CALLBACK(gtk_menu_item_application_menu_callback),
//                               pcommandhandler);
//
//             // gtkactionentriea[iEntry].stock_id = g_strdup(scopedstrId);
//
//             // gtkactionentriea[iEntry].label = g_strdup(scopedstrName);
//
//             // //gtkactionentriea[iEntry].accelerator = g_strdup(scopedstrAccelerator);
//
//             // //gtkactionentriea[iEntry].accelerator = nullptr;
//
//             // gtkactionentriea[iEntry].accelerator = g_strdup("");
//
//             // gtkactionentriea[iEntry].tooltip = g_strdup(scopedstrDescription);
//
//             // gtkactionentriea[iEntry].callback = G_CALLBACK (user_notify_icon_bridge_extra_action);
//
//             // iEntry++;
//
//          }
//
//       }
//
//       gtk_widget_show (pgtkwidget);
//
//       gtk_menu_shell_append (GTK_MENU_SHELL (pgtkwidgetMenu), pgtkwidget);
//
//       //gtk_container_add (GTK_CONTAINER (pgtkwidgetMenu), pgtkwidget);
//
//    }
//
//    return GTK_MENU(pgtkwidgetMenu);
//
//
// }


#include "appindicator.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"


namespace node_x11
{


   appindicator::appindicator()
   {

      //m_pindicator = nullptr;

   }


   appindicator::~appindicator()
   {

   }


   bool appindicator::create(
      const ::scoped_string & scopedstrId,
      const ::scoped_string & scopedstrIcon,
      const ::scoped_string & scopedstrFolder,
      application_menu * papplicationmenu,
      command_handler * pcommandhandler)
   {

//#if defined(HAS_GTK4)
//      ::pointer < ::node_gtk4::node > pgtknode = node();
//#elif defined(HAS_GTK3)
//      ::pointer < ::node_gtk3::node > pgtknode = node();
//#endif
//
//      if(!pgtknode->os_defer_init_gtk())
//      {
//
//         return false;
//
//      }

      // m_pindicator = app_indicator_new_with_path(scopedstrId, scopedstrIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, scopedstrFolder);
      //
      // if(m_pindicator == nullptr)
      // {
      //
      //    return false;
      //
      // }
      //
      // if(!init(papplicationmenu, pcommandhandler))
      // {
      //
      //    close();
      //
      //    return false;
      //
      // }

      return true;

   }


   bool appindicator::init(application_menu * papplicationmenu, ::command_handler * pcommandhandler)
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

      throw todo;
      //auto pgtkmenu = gtk_menu_from_application_menu(papplicationmenu, pcommandhandler);

//      for(int i = 0; i < iCount; i++)
//      {
//
//         const_char_pointer pszName = pbridge->_get_notification_area_action_name(i);
//         const_char_pointer pszId = pbridge->_get_notification_area_action_id(i);
//         const_char_pointer pszLabel = pbridge->_get_notification_area_action_label(i);
//         const_char_pointer pszAccelerator = pbridge->_get_notification_area_action_accelerator(i);
//         const_char_pointer pszDescription = pbridge->_get_notification_area_action_description(i);
//
//         GtkWidget * pgtkwidget = nullptr;
//
//         if(ansi_icmp(scopedstrName, "separator") == 0)
//         {
//
//   	      pgtkwidget = gtk_separator_menu_item_new();
//
//         }
//         else
//         {
//
//            pgtkwidget = gtk_menu_item_new_with_label(scopedstrLabel);
//
//            gtk_widget_set_name(GTK_WIDGET(pgtkwidget), pszId);
//
//            g_signal_connect (G_OBJECT(pgtkwidget), "activate", G_CALLBACK (user_notify_icon_bridge_extra_action), pbridge);
//
//            // gtkactionentriea[iEntry].stock_id = g_strdup(scopedstrId);
//
//            // gtkactionentriea[iEntry].label = g_strdup(scopedstrName);
//
//            // //gtkactionentriea[iEntry].accelerator = g_strdup(scopedstrAccelerator);
//
//            // //gtkactionentriea[iEntry].accelerator = nullptr;
//
//            // gtkactionentriea[iEntry].accelerator = g_strdup("");
//
//            // gtkactionentriea[iEntry].tooltip = g_strdup(scopedstrDescription);
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

      // informationf("appindicator::init GtkMenu = %" PRI0xPTR, (long unsigned int) pgtkmenu);
      //
      // app_indicator_set_menu(m_pindicator, pgtkmenu);
      //
      // app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_ACTIVE);

      return true;

   }


   void appindicator::close()
   {


      // if(m_pindicator == NULL)
      // {
      //
      //    return;
      //
      // }
      //
      // auto pindicator = m_pindicator;
      //
      // user_post([pindicator]()
      //          {
      //
      //             app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);
      //
      //          });
      //
      // m_pindicator = NULL;

   }


} // namespace node_x11



