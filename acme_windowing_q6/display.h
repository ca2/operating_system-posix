//
// From acme_windowing_gkt3/display on 2025-01-10 01:18 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_q/display.h"
//#include "event_listener.h"
//#include "windowing_system_x11/_atom.h"
#include <QWidget>


namespace q6
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_Q6 display :
            virtual public ::q::acme::windowing::display
         {
         public:

            display();
            ~display() override;


         };


      } // namespace windowing


   } // namespace acme


} // namespace q6



