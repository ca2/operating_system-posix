#include "framework.h"


namespace draw2d_xlib
{



   object::object()
   {
      //set_handle(nullptr);
   }

   object::~object()
   {
      //delete_object();
   }

   i32 object::get_object(i32 nCount, LPVOID lpObject) const
   {
      //return ::GetObject(get_handle(), nCount, lpObject);
      return 0;
   }

   bool object::CreateStockObject(i32 nIndex)
   {
      //return (set_handle(::GetStockObject(nIndex))) != nullptr;
      return 0;
   }
   bool object::UnrealizeObject()
   {
      //ASSERT(get_handle() != nullptr); return ::UnrealizeObject(get_handle());
      return 0;
   }
   ::u32 object::GetObjectType() const
   {
      //return (::u32)::GetObjectType(get_handle());
      return 0;
   }

   object * graphics_object_allocator(::particle * pparticle, HANDLE h)
   {
      return nullptr;
   }


   bool object::delete_object()
   {
      return false;
   }



   void object::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

   }

   void object::assert_ok() const
   {
      ::object::assert_ok();
   }



   void * object::get_os_data() const
   {

      return nullptr;

   }


} // namespace draw2d_xlib






