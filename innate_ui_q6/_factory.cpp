#include "framework.h"
#include "dialog.h"
#include "icon.h"
#include "window.h"
#include "button.h"
#include "still.h"
#include "innate_ui.h"



IMPLEMENT_FACTORY(innate_ui_q6)
{


   pfactory->add_factory_item < ::innate_ui_q6::window, ::innate_ui::window >();
   pfactory->add_factory_item < ::innate_ui_q6::dialog, ::innate_ui::dialog >();
   
   
   pfactory->add_factory_item < ::innate_ui_q6::button, ::innate_ui::button >();
   pfactory->add_factory_item < ::innate_ui_q6::still, ::innate_ui::still >();


   pfactory->add_factory_item < ::innate_ui_q6::icon, ::innate_ui::icon >();


   pfactory->add_factory_item < ::innate_ui_q6::innate_ui, ::innate_ui::innate_ui >();

}



