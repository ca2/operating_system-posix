#pragma once


class xcb_hook :
virtual public ::matter
{
public:



   xcb_hook();


   virtual bool process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie);

   ::e_status hook();
   ::e_status unhook();

   virtual void on_idle(xcb_connection_t * pdisplay);

};



