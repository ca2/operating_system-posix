#pragma once


class simple_ui_display :
   virtual public ::x11_hook
{
public:


   bool                             m_bOsUserThemeColorModified;
   bool                             m_bInvalidated;
   string_array                     m_stra;
   string                           m_strTitle;
   string                           m_strFontName;

   Window                           m_window;
   ::point_i32                          m_point;
   ::size                           m_size;

   int                              m_iLineHeight;
   int                              m_iTextAscent;

   pointer_array < x11_button >      m_buttona;

   int                              m_iButtonTop;
   int                              m_iButtonHeight;
   int                              m_iButtonWidth;

   XftFont *                        m_pfont;
   XftDraw *                        m_pdraw;
   //XFontSet                         m_fs;
   //char **                          m_listMissingCharset;
   //GC                               m_gcText;
   //GC                               m_gcTextHover;
   //GC                               m_gcBar;
   XftColor                         m_colorButton;
   XftColor                         m_colorButtonHover;
   XftColor                         m_colorButtonPress;
   XftColor                         m_colorBorder;
   XftColor                         m_colorBorderHover;
   XftColor                         m_colorBorderPress;
   XftColor                         m_colorBorderHover1;
   XftColor                         m_colorBorderHover2;
   XftColor                         m_colorBorderHover3;

   Colormap                         m_colormap;
   int                              m_iScreen;
   Visual *                         m_pvisual;
   int                              m_iMarginTop;
   int                              m_iMarginLeft;
   int                              m_iMarginRight;
   int                              m_iMarginBottom;
   int                              m_iLineSpacing;
   int                              m_iButtonHSpacing;
   int                              m_iButtonHPadding;
   int                              m_iButtonVPadding;
   int                              m_iMidSpacing;

   XftColor                         m_colorBack;
   XftColor                         m_colorFace;
   XftColor                         m_colorFore;

   XftColor                         m_colorFaceHover;
   XftColor                         m_colorFacePress;

   int                              m_iResult;


   simple_ui_display(const string & strMessage, const string & strTitle, const ::e_message_box & emessagebox);
   ~simple_ui_display();


   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


   void common_construct();

   //GC create_gc();

   virtual void invalidate();

   virtual void on_idle(Display * pdisplay) override;

   void on_expose(Display * pdisplay);

   void call_expose(Display * pdisplay);

   virtual void on_subject(::promise::topic * ptopic, ::context * pcontext) override;

   void on_layout(Display * pdisplay);

   void on_colors(Display * pdisplay);

   void on_alloc_colors(Display * pdisplay);

   void on_free_colors(Display * pdisplay);

   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie) override;

   int show();

   void on_show();

   bool on_click(int iResult);

   virtual void close_window();


};


