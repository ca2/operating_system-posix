#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_x11)
{

   pfactory->add_factory_item < ::x11::windowing_system::windowing_system, ::windowing_system::windowing_system >();

}



void * node::x11_get_display()
{

   x11_defer_initialize();

   if(m_pvoidX11Display == NULL)
   {

      m_pvoidX11Display =  XOpenDisplay(NULL);

   }

   return m_pvoidX11Display;

}
