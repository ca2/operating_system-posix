#pragma once


#include "node_q/copydesk.h"


namespace node_lxq1
{


   class CLASS_DECL_NODE_LXQ1 copydesk :
      virtual public ::node_q::copydesk
   {
   public:


      copydesk();
      ~copydesk() override;

      //
      // void initialize(::particle * pparticle) override;
      // void destroy() override;
      //
      // bool _set_filea(const ::file::path_array_base & patha, enum_op eop) override;
      // bool _get_filea(::file::path_array_base & patha, enum_op & eop) override;
      // bool _has_filea() override;
      //
      //
      // //virtual bool set_plain_text(const ::scoped_string & scopedstr) override;
      // bool _set_plain_text(const ::scoped_string & scopedstr) override;
      // bool _get_plain_text(string & str) override;
      // bool _has_plain_text() override;
      //
      // bool _desk_to_image(::image::image *pimage) override;
      // bool _image_to_desk(const ::image::image *pimage) override;
      // bool _has_image() override;

   };


} // namespace node_lxq1



