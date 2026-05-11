#pragma once


namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB object :
      virtual public ::draw2d::object
   {
   public:


      object();
      virtual ~object();


      virtual void * get_os_data() const;


      bool delete_object();


      int get_object(int nCount, LPVOID lpObject) const;
      ::u32 GetObjectType() const;
      bool CreateStockObject(int nIndex);
      bool UnrealizeObject();
      //bool operator==(const object& obj) const;
      //bool operator!=(const object& obj) const;

      // void dump(dump_context & dumpcontext) const override;
      void assert_ok() const override;

   };


} // namespace draw2d_xlib
