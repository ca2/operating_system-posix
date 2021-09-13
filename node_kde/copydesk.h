#pragma once


namespace node_kde
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::user::copydesk
   {
   public:


      copydesk();
      ~copydesk() override;


      ::e_status initialize(::object * pobject) override;
      ::e_status destroy() override;

      ::e_status _set_filea(const ::file::patha & patha, e_op eop) override;
      ::e_status _get_filea(::file::patha & patha, e_op & eop) override;
      bool _has_filea() override;


      //virtual bool set_plain_text(const string & str) override;
      ::e_status _set_plain_text(const string & str) override;
      ::e_status _get_plain_text(string & str) override;
      bool _has_plain_text() override;

      ::e_status _desk_to_image(::image * pimage) override;
      ::e_status _image_to_desk(const ::image * pimage) override;
      bool _has_image() override;

   };


} // namespace node_kde



