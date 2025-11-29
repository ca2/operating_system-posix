#include "framework.h"


namespace draw2d_xlib
{


   factory_exchange::factory_exchange()
   {

      init_xlib_mutex(pparticle);

      add_factory_item < image                   >  (typeid(pimage));
      add_factory_item < graphics              >  (typeid(::draw2d::graphics));
      add_factory_item < bitmap                >  (typeid(::draw2d::bitmap));
      add_factory_item < pen                   >  (typeid(::draw2d::pen));
      add_factory_item < brush                 >  (typeid(::draw2d::brush));
      add_factory_item < palette               >  (typeid(::draw2d::palette));
      add_factory_item < region                >  (typeid(::draw2d::region));
      add_factory_item < font                  >  (typeid(::write_text::font ));
      add_factory_item < path                  >  (typeid(::draw2d::path));

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


