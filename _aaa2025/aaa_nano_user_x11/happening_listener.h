//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include <X11/Xlib.h>
//#include "acme/prototype/prototype/element.h"


namespace x11
{


   class event_listener :
      virtual public ::particle
   {
   public:


      virtual bool _on_x11_event(::x11::event_t * pevent);


   };


} // namespace x11



