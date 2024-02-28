#pragma once


#include "aura/user/user/copydesk.h"


namespace node_kde
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::user::copydesk
   {
   public:


      copydesk();
      ~copydesk() override;


      void initialize(::particle * pparticle) override;
      void destroy() override;

      bool _set_filea(const ::file::path_array & patha, enum_op eop) override;
      bool _get_filea(::file::path_array & patha, enum_op & eop) override;
      bool _has_filea() override;


      //virtual bool set_plain_text(const string & str) override;
      bool _set_plain_text(const string & str) override;
      bool _get_plain_text(string & str) override;
      bool _has_plain_text() override;

      bool _desk_to_image(::image * pimage) override;
      bool _image_to_desk(const ::image * pimage) override;
      bool _has_image() override;

   };


} // namespace node_kde



