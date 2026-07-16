#pragma once


#include "_.h"
#include "acme/accessibility/application.h"


namespace accessibility_gtk4
{


   class CLASS_DECL_ACCESSIBILITY_GTK4 application :
      virtual public ::accessibility::application
   {
   public:


      application();
      ~application() override;


   };


} // namespace accessibility_gtk4
