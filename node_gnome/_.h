#pragma once


#include "node_linux/_.h"
#include "windowing_x11/_.h"
#include "acme/os/linux/_linux.h"
#include "acme/os/ansios/_pthread.h"
#include "aura/user/_user.h"
#include "aura/os/linux/appindicator.h"


#include <gtk/gtk.h>
#include <gdk/gdkx.h>


#if defined(_NODE_GNOME_LIBRARY)
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_IMPORT
#endif


namespace node_gnome
{


   class node;


} // namespace node_gnome


#undef Node
#define Node (::get_context_system()->m_pnode ? ::get_context_system()->m_pnode->cast < ::node_gnome::node > () : nullptr)


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


#include "monitor.h"


#include "display.h"


#include "node.h"


#include "windowing.h"


#include "copydesk.h"


#include "appindicator.h"


#include "notify_icon.h"


#include "factory_exchange.h"



