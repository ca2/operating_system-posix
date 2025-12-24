//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_x11/_x11.h"
//#include "acme/prototype/prototype/element.h"


namespace x11
{

   namespace acme
   {

      namespace windowing
      {



   class happening_listener :
      virtual public ::particle
   {
   public:


      virtual bool __on_x11_event(XEvent * pevent);


   };



      }
   }



} // namespace x11



