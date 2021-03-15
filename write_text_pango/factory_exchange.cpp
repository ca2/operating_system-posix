#include "framework.h"


extern "C"
void write_text_pango_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::write_text_pango::font_department, ::font_department >();
   pfactorymap->create_factory < ::write_text_pango::write_text, ::write_text::write_text >();

}