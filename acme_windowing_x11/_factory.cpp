#include "framework.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_x11)
{

   pfactory->add_factory_item < ::x11::acme::windowing::windowing, ::acme::windowing::windowing >();

}


//
//void * node::x11_get_display()
//{
//
//   x11_defer_initialize();
//
//   if(m_pvoidX11Display == NULL)
//   {
//
//      m_pvoidX11Display =  XOpenDisplay(NULL);
//
//   }
//
//   return m_pvoidX11Display;
//
//}
