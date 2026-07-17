#pragma once


#include "_.h"
#include "acme/accessibility/main_window.h"


namespace accessibility_kde6
{


   class CLASS_DECL_ACCESSIBILITY_KDE6 main_window :
      virtual public ::accessibility::main_window
   {
   public:


      main_window();
      ~main_window() override;


   };


} // namespace accessibility_kde6
