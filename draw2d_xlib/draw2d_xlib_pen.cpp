#include "framework.h"


namespace draw2d_xlib
{


   pen::pen(::particle * pparticle) :
      ::object(pparticle)
   {
   }
   pen::~pen()
   {
   }

#ifdef _DEBUG

   void pen::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

   }

#endif




      // IMPLEMENT_DYNAMIC(resource_exception, ::exception)
      //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

      // IMPLEMENT_DYNAMIC(user_exception, ::exception)
      //user_exception _simpleUserException(false, __IDS_USER_EXCEPTION);

      // IMPLEMENT_DYNCREATE(::draw2d::graphics_pointer, object)
      // IMPLEMENT_DYNAMIC(CClientDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CWindowDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CPaintDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNCREATE(object, object)

      // IMPLEMENT_DYNAMIC(pen, object)
      // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
      // IMPLEMENT_DYNAMIC(::write_text::font, object)
      // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
      // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
      // IMPLEMENT_DYNAMIC(::aura::rgn, object)

      /////////////////////////////////////////////////////////////////////////////
      // Standard exception processing


   void * pen::get_os_data() const
   {
   return nullptr;
   }

} // namespace draw2d_xlib




