#include "framework.h"
#include "dialog.h"
#include "icon.h"
#include "window.h"
#include "button.h"
#include "still.h"
#include "innate_ui.h"



IMPLEMENT_FACTORY(innate_ui_xaw)
{

   pfactory->add_factory_item < ::innate_ui_xaw::window, ::innate_ui::window >();
   pfactory->add_factory_item < ::innate_ui_xaw::dialog, ::innate_ui::dialog >();
   
   
   pfactory->add_factory_item < ::innate_ui_xaw::button, ::innate_ui::button >();
   pfactory->add_factory_item < ::innate_ui_xaw::still, ::innate_ui::still >();


   pfactory->add_factory_item < ::innate_ui_xaw::icon, ::innate_ui::icon >();


   pfactory->add_factory_item < ::innate_ui_xaw::innate_ui, ::innate_ui::innate_ui >();

}



