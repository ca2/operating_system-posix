#pragma once


namespace write_text_pango
{


   class CLASS_DECL_WRITE_TEXT_PANGO font_enumeration :
virtual public ::write_text::font_enumeration
   {
   public:



      font_enumeration();
      ~font_enumeration() override;



      ::e_status on_enumerate_fonts() override;


   };


} // namespace write_text_pango



