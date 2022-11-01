// Created by camilo 2021-01
// Recreated by camilo 2021-02-10 <3TBS_!!
#include "framework.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "font_enumeration.h"
#include <pango/pangocairo.h>


namespace write_text_pango
{

   font_enumeration::font_enumeration()
   {


   }


   font_enumeration::~font_enumeration()
   {


   }


   void font_enumeration::on_enumerate_fonts()
   {

      //synchronous_lock ml(cairo_mutex());

      __defer_construct_new(m_pfontenumerationitema);

      m_pfontenumerationitema->erase_all();

      PangoFontMap * pfontmap = pango_cairo_font_map_get_default();

      PangoFontFamily ** families;

      int n_families = 0;

      pango_font_map_list_families(pfontmap, &families, &n_families);

      printf("Total fonts: %d", n_families);

      for (int i = 0; i < n_families; i++)
      {

         auto pitem = __new(::write_text::font_enumeration_item);

         PangoFontFamily * pfamily = families[i];

         string strFileName = pango_font_family_get_name(pfamily);

         pitem->m_mapFileName[0] = strFileName;

         pitem->m_strName = strFileName;

         m_pfontenumerationitema->add(pitem);

      }

      g_free(families);

      //return ::success;

   }


} // namespace write_text_pango



