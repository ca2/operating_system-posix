// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/graphics/write_text/fonts.h"


namespace write_text_pango
{


   class CLASS_DECL_WRITE_TEXT_PANGO fonts :
      virtual public ::write_text::fonts
   {
   public:


    /*  ::pointer<::write_text::font_enumeration>  m_pfontenumeration;*/

      //::write_text::font_pointer                m_pfontCaption;
      //::write_text::font_pointer                m_pfontMenu;
      //::write_text::font_pointer                m_pfontStandard;
      //::write_text::font_pointer                m_pfont;
      //::write_text::font_pointer                m_pfontListCtrl;
      //::write_text::font_pointer                m_pfontMeshCtrl;
      //::write_text::font_pointer                m_pfontGridCtrl;
      //::pointer<::write_text::font>                m_lpSongLabelFont;
      //::pointer<::write_text::font>                m_lpSongListFont;
      //::pointer<::write_text::font>                m_pfontLyric;
      //::pointer<::write_text::font>                m_pfontLyricCompact;
      //::pointer<::write_text::font>                m_pxffontMidiTrackName;
      //draw2d_font_spa              m_pTitleFonts;
      //draw2d_font_spa              m_pSubTitleFonts;
      //draw2d_font_spa              m_pH3TitleFonts;
      //bool                             m_bInitialized;
      //bool                             m_bLyric;


      //::write_text::font * GetListCtrlFont();
      //::write_text::font * GetMeshCtrlFont();
      //::write_text::font * GetGridCtrlFont();
      //::write_text::font * GetCaptionFont();
      //::write_text::font * GetStandartFont();
      //::write_text::font * GetSongListFont();
      //::write_text::font * GetSongLabelFont();
      //::write_text::font * GetTitleFont();
      //::write_text::font * GetSubTitleFont();
      //::write_text::font * GetH3TitleFont();
      //::write_text::font * GetMidiTrackNameFont();
      //::write_text::font * GetMenuFont();
      //::write_text::font * GetLyricWindowFont();
      //::write_text::font * GetLyricWindowCompactFont();
      //draw2d_font_spa & GetTitleFonts();
      //draw2d_font_spa & GetSubTitleFonts();
      //draw2d_font_spa & GetH3TitleFonts();

      //void CreateLyricWindowFonts();
      //void DestroyLyricWindowFonts();


      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;
      //virtual ::e_status finalize() override;


      //virtual bool is_initialized();
      //virtual void defer_create_font_enumeration(::promise::topic * ptopic);


      //virtual void enum_fonts(::write_text::font_enum_item_array & itema) override;
      //virtual void sorted_fonts(::write_text::font_enum_item_array & itema);


   };


} // namespace write_text_pango



