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




#include "gnome_shared.h"




