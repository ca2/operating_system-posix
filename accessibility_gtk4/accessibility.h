#pragma once


#include "_.h"
#include "acme/accessibility/accessibility.h"


namespace accessibility_gtk4
{


   class CLASS_DECL_ACCESSIBILITY_GTK4 accessibility :
      virtual public ::accessibility::accessibility
   {
   public:


      accessibility();
      ~accessibility() override;


   };


} // namespace accessibility_gtk4
