#pragma once


#include "aura_linux/_.h"
#include "windowing_xcb/_.h"
#include "acme/os/linux/_linux.h"
#include "acme/os/ansios/_pthread.h"
#include "aura/user/_user.h"
#include "aura/os/linux/appindicator.h"
#include "platform-posix/windowing_xcb/_.h"


#if defined(_NODE_KDE_LIBRARY)
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_IMPORT
#endif


namespace node_kde
{


   class node;


} // namespace node_kde


//namespace user
//{
//
//
//   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);
//
//
//} // namespace user


#include "copydesk.h"


#include "appindicator.h"


#include "factory_exchange.h"



