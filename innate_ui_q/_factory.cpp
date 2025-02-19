#include "framework.h"
#include "dialog.h"
#include "icon.h"
#include "window.h"
#include "button.h"
#include "still.h"
#include "innate_ui.h"



IMPLEMENT_FACTORY(innate_ui_q)
{


   pfactory->add_factory_item < ::innate_ui_q::window, ::innate_ui::window >();
   pfactory->add_factory_item < ::innate_ui_q::dialog, ::innate_ui::dialog >();
   
   
   pfactory->add_factory_item < ::innate_ui_q::button, ::innate_ui::button >();
   pfactory->add_factory_item < ::innate_ui_q::still, ::innate_ui::still >();


   pfactory->add_factory_item < ::innate_ui_q::icon, ::innate_ui::icon >();


   pfactory->add_factory_item < ::innate_ui_q::innate_ui, ::innate_ui::innate_ui >();

}



