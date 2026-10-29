#pragma once


#include "_.h"
#include "acme/accessibility/accessibility.h"
#include <memory>


namespace accessibility_kde6
{
   class kwin_bridge;


   class CLASS_DECL_ACCESSIBILITY_KDE6 accessibility :
      virtual public ::accessibility::accessibility
   {
   public:


      accessibility();
      ~accessibility() override;
      bool get_window_geometry(::process_identifier processidentifier,
         const ::scoped_string & title, ::accessibility::window_geometry & geometry,
         const ::scoped_string & windowId = {}) override;
   private:
      std::unique_ptr<kwin_bridge> m_kwin;



   };


} // namespace accessibility_kde6
