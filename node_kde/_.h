#pragma once


#include "node_linux/_.h"
#include "windowing_xcb/_.h"
#include "acme/os/linux/_linux.h"
#include "acme/os/ansios/_pthread.h"
#include "aura/user/_user.h"
#include "aura/os/linux/appindicator.h"


#if defined(_NODE_GNOME_LIBRARY)
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_IMPORT
#endif

#undef new
#include <qmetatype.h>
#include <QApplication>
#include <QPalette>
#include <QAbstractNativeEventFilter>
#define new ACME_NEW

namespace node_kde
{


   class node;


} // namespace node_kde


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


} // namespace user


#include "node.h"


#include "copydesk.h"


#include "appindicator.h"


#include "factory_exchange.h"



