#include "framework.h"
#include "_xcb.h"
#include "acme/parallelization/synchronous_lock.h"




xcb_hook::xcb_hook()
{

}


pointer_array < xcb_hook > g_xcbhooka;


void xcb_hook::hook()
{

   _synchronous_lock synchronouslock(x11_mutex());

   g_xcbhooka.add(this);

   return ::success;

}


void xcb_hook::unhook()
{

   _synchronous_lock synchronouslock(x11_mutex());

   g_xcbhooka.erase(this);

   return ::success;

}


void xcb_hook::on_idle(Display * pdisplay)
{

}


bool __xcb_hook_list_is_empty()
{

   return g_xcbhooka.is_empty();

}


bool __xcb_hook_process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie)
{

   for(auto & phook : g_xcbhooka)
   {

      if(phook->process_event(pdisplay, pevent, cookie))
      {

         return true;

      }

   }

   return false;

}


void __xcb_hook_on_idle(Display * pdisplay)
{

   for(auto & phook : g_xcbhooka)
   {

      phook->on_idle(pdisplay);

   }

}


#if !defined(RASPBERRYPIOS)

bool x11_process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);

#else

bool x11_process_event(Display * pdisplay, XEvent & e);

#endif


bool __xcb_hook_process_event(Display * pdisplay, xcb_generic_event_t * pevent);


bool xcb_hook::process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie)
{

   return false;

}


void xcb_hook_init()
{


}


void xcb_hook_term()
{

    g_xcbhooka.erase_all();

}



