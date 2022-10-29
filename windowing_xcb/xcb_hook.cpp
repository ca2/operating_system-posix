#include "framework.h"
#include "_xcb.h"


//pointer_array < xcb_hook > * g_pxcbhooka;

//void xcb_hook_init()
//{
//
//  g_pxcbhooka = memory_new pointer_array < xcb_hook >;
//
//}


//void xcb_hook_term()
//{
//
//   ::acme::del(g_pxcbhooka);
//
//}

//LPFN_X11_PROCESS_EVENT g_xcbprocesseventa[8];


xcb_hook::xcb_hook()
{

}


pointer_array < xcb_hook > g_xcbhooka;


::e_status xcb_hook::hook()
{

   synchronous_lock sl(user_synchronization());

   g_xcbhooka.add(this);

   return ::success;

}


::e_status xcb_hook::unhook()
{

   synchronous_lock sl(user_synchronization());

   g_xcbhooka.remove(this);

   return ::success;

}


void xcb_hook::on_idle(xcb_connection_t * pdisplay)
{

}


bool __xcb_hook_list_is_empty()
{

   return g_xcbhooka.is_empty();

}


bool windowing::__xcb_hook_process_event(xcb_generic_event_t * pevent, XGenericEventCookie * cookie)
{

   XEvent & e = *pevent;

   for(auto & phook : g_xcbhooka)
   {

      if(phook->process_event(pdisplay, e, cookie))
      {

         return true;

      }

   }

   return false;

}


void __xcb_hook_on_idle(xcb_connection_t * pdisplay)
{

   for(auto & phook : g_xcbhooka)
   {

      phook->on_idle(pdisplay);

   }

}


#if !defined(RASPBIAN)

bool xcb_process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie);

#else

bool xcb_process_event(xcb_connection_t * pdisplay, XEvent & e);

#endif


bool __xcb_hook_process_event(xcb_connection_t * pdisplay, XEvent & e);


bool xcb_hook::process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie)
{

   return false;

}


void xcb_hook_init()
{


}


void xcb_hook_term()
{

    g_xcbhooka.remove_all();

}



//bool __xcb_hook_process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie)
//{
//
//   for(auto & phook : g_xcbhooka)
//   {
//
//      if(phook->process_event(pdisplay, e, cookie))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}



