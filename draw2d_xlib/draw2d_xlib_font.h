#pragma once

typedef struct _XftFont XftFont;



namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB font :
      virtual public ::write_text::font
   {
   public:

      Display * m_pdisplay;
      XFontStruct * m_pfont;
      XFontSet m_fontset;
      XftFont *      m_pft;

      font(::particle * pparticle);
      virtual ~font();


      virtual void * get_os_data() const;

      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace draw2d_xlib



