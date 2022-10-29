#include "framework.h"
#include "_x11.h"


//pointer_array < x11_hook > * g_px11hooka;

//void x11_hook_init()
//{
//
//  g_px11hooka = memory_new pointer_array < x11_hook >;
//
//}


//void x11_hook_term()
//{
//
//   ::acme::del(g_px11hooka);
//
//}

//LPFN_X11_PROCESS_EVENT g_x11processeventa[8];


x11_hook::x11_hook()
{

}


pointer_array < x11_hook > g_x11hooka;


::e_status x11_hook::hook()
{

   synchronous_lock sl(user_synchronization());

   g_x11hooka.add(this);

   return ::success;

}


::e_status x11_hook::unhook()
{

   synchronous_lock sl(user_synchronization());

   g_x11hooka.remove(this);

   return ::success;

}


void x11_hook::on_idle(Display * pdisplay)
{

}


bool __x11_hook_list_is_empty()
{

   return g_x11hooka.is_empty();

}


bool windowing::__x11_hook_process_event(XEvent * pevent, XGenericEventCookie * cookie)
{

   XEvent & e = *pevent;

   for(auto & phook : g_x11hooka)
   {

      if(phook->process_event(pdisplay, e, cookie))
      {

         return true;

      }

   }

   return false;

}


void __x11_hook_on_idle(Display * pdisplay)
{

   for(auto & phook : g_x11hooka)
   {

      phook->on_idle(pdisplay);

   }

}


#if !defined(RASPBIAN)

bool x11_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);

#else

bool x11_process_event(Display * pdisplay, XEvent & e);

#endif


bool __x11_hook_process_event(Display * pdisplay, XEvent & e);


bool x11_hook::process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
{

   return false;

}


void x11_hook_init()
{


}


void x11_hook_term()
{

    g_x11hooka.remove_all();

}



//bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
//{
//
//   for(auto & phook : g_x11hooka)
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



