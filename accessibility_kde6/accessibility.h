#pragma once


#include "_.h"
#include "acme/accessibility/accessibility.h"


namespace accessibility_kde6
{


   class CLASS_DECL_ACCESSIBILITY_KDE6 accessibility :
      virtual public ::accessibility::accessibility
   {
   public:


      accessibility();
      ~accessibility() override;


   };


} // namespace accessibility_kde6
