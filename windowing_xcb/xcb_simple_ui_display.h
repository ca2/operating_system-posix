#pragma once


class simple_ui_display :
   virtual public ::xcb_hook
{
public:


   bool                             m_bOsUserThemeColorModified;
   bool                             m_bInvalidated;
   string_array                     m_stra;
   string                           m_strTitle;
   string                           m_strFontName;

   xcb_window_t                           m_window;
   ::int_point                          m_point;
   ::size                           m_size;

   int                              m_iLineHeight;
   int                              m_iTextAscent;

   pointer_array < xcb_button >      m_buttona;

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


   simple_ui_display(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox);
   ~simple_ui_display();


   virtual long long increment_reference_count();
   virtual long long decrement_reference_count();
   virtual long long release();


   void common_construct();

   //GC create_gc();

   virtual void invalidate();

   virtual void on_idle(xcb_connection_t * pdisplay) override;

   void on_expose(xcb_connection_t * pdisplay);

   void call_expose(xcb_connection_t * pdisplay);

   virtual void on_subject(::promise::topic * ptopic, ::handler_context * pcontext) override;

   void on_layout(xcb_connection_t * pdisplay);

   void on_colors(xcb_connection_t * pdisplay);

   void on_alloc_colors(xcb_connection_t * pdisplay);

   void on_free_colors(xcb_connection_t * pdisplay);

   virtual bool process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie) override;

   int show();

   void on_show();

   bool on_click(int iResult);

   virtual void close_window();


};


