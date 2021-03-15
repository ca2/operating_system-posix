// Created by camilo 2021-02-10 <3TBS_!!
#include "framework.h"
#include "acme/os/ansios/_pthread.h"
#include <pango/pangocairo.h>


namespace write_text_pango
{


   font_department::font_department()
   {


   }


   font_department::~font_department()
   {


   }


   ::e_status font_department::initialize(::layered * pobjectContext)
   {

      auto estatus = ::font_department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void font_department::finalize()
   {

      ::font_department::finalize();

   }


   void font_department::enum_fonts(::write_text::font_enum_item_array & itema)
   {

      //synchronization_lock ml(cairo_mutex());

      PangoFontMap * pfontmap = pango_cairo_font_map_get_default();

      PangoFontFamily ** families;

      int n_families = 0;

      pango_font_map_list_families(pfontmap, &families, &n_families);

      printf("Total fonts: %d", n_families);

      __pointer(::write_text::font_enum_item) item;

      for (int i = 0; i < n_families; i++)
      {

         item = __new(::write_text::font_enum_item);

         PangoFontFamily * pfamily = families[i];

         string strFileName = pango_font_family_get_name(pfamily);

         item->m_mapFileName[0] = strFileName;

         item->m_strName = strFileName;

         itema.add(item);

      }

      g_free(families);

   }


} // namespace write_text_pango



