//
// Created by camilo on 09/04/2022.
//
#pragma once


#include "acme/_.h"



#if defined(_acme_windowing_x11_project)
#define CLASS_DECL_ACME_WINDOWING_X11  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWING_X11  CLASS_DECL_IMPORT
#endif



void x11_check_status(int status, unsigned long window);


namespace x11
{

   namespace acme
   {



      namespace windowing
      {


         class display;
         class window;


         class windowing;


      } // namespace windowing







   } // namespae acme




} // namespace acme_windowing_x11

