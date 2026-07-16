#pragma once


#include "_.h"
#include "acme/accessibility/main_window.h"


namespace accessibility_gtk4
{


   class CLASS_DECL_ACCESSIBILITY_GTK4 main_window :
      virtual public ::accessibility::main_window
   {
   public:


      main_window();
      ~main_window() override;


   };


} // namespace accessibility_gtk4
