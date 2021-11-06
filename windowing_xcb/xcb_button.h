#pragma once


//!!!#include <X11/Xft/Xft.h>


class xcb_button :
   virtual public matter
{
public:


   string               m_strLabel;
   bool                 m_bTextRect;
   ::rectangle_i32               m_rect;
   XGlyphInfo           m_infoText;
   bool                 m_bPress;
   bool                 m_bHover;
   enum_dialog_result   m_edialogresult;


   xcb_button(const char * psz, enum_dialog_result edialogresult);

   virtual ~xcb_button();


};



