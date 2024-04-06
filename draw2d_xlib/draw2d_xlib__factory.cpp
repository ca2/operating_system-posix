#include "framework.h"


namespace draw2d_xlib
{


   factory_exchange::factory_exchange()
   {

      init_xlib_mutex(pparticle);

      add_factory_item < image                   >  (::type < pimage >());
      add_factory_item < graphics              >  (::type < ::draw2d::graphics >());
      add_factory_item < bitmap                >  (::type < ::draw2d::bitmap >());
      add_factory_item < pen                   >  (::type < ::draw2d::pen >());
      add_factory_item < brush                 >  (::type < ::draw2d::brush >());
      add_factory_item < palette               >  (::type < ::draw2d::palette >());
      add_factory_item < region                >  (::type < ::draw2d::region >());
      add_factory_item < font                  >  (::type < ::write_text::font >());
      add_factory_item < path                  >  (::type < ::draw2d::path >());

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace win


extern "C"
void factory_exchange()
{
   draw2d_xlib::factory_exchange factoryexchange();
}


