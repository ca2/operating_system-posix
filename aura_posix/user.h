#pragma once


// GDK, GTK :: C

extern "C"
{


   void linux_g_direct_init();
   void linux_g_direct_term();
   //void * linux_g_direct_app_indicator_new(const_char_pointer pszId, const_char_pointer pszIcon, const_char_pointer pszFolder, struct user_notify_icon_bridge * pbridge);
   void linux_g_direct_step(void * pind);
   //void linux_g_direct_app_indicator_term(void * pind);


} // extern "C"


//struct user_notify_icon_bridge
//{
//public:
//
//
//   virtual int _get_notification_area_action_count() = 0;
//   virtual bool _get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex) = 0;
//   virtual void call_notification_area_action(const_char_pointer pszId) = 0;
//
//
//};


#include "gnome_shared.h"




