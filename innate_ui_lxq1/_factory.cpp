#include "framework.h"
#include "dialog.h"
#include "icon.h"
#include "window.h"
#include "button.h"
#include "still.h"
#include "innate_ui.h"



IMPLEMENT_FACTORY(innate_ui_lxq1)
{


   pfactory->add_factory_item < ::innate_ui_lxq1::window, ::innate_ui::window >();
   pfactory->add_factory_item < ::innate_ui_lxq1::dialog, ::innate_ui::dialog >();
   
   
   pfactory->add_factory_item < ::innate_ui_lxq1::button, ::innate_ui::button >();
   pfactory->add_factory_item < ::innate_ui_lxq1::still, ::innate_ui::still >();


   pfactory->add_factory_item < ::innate_ui_lxq1::icon, ::innate_ui::icon >();


   pfactory->add_factory_item < ::innate_ui_lxq1::innate_ui, ::innate_ui::innate_ui >();

}



