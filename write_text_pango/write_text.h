// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/graphics/write_text/write_text.h"


namespace write_text_pango
{


   class CLASS_DECL_WRITE_TEXT_PANGO write_text :
      virtual public ::write_text::write_text
   {
   public:


      write_text();
      virtual ~write_text();

      //virtual void enum_fonts(font_enum_item_array & itema);
      //virtual void sorted_fonts(font_enum_item_array & itema);



   };


} // namespace write_text_pango



