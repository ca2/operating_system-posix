#include "framework.h"
#include "_xcb.h"


xcb_button::xcb_button(const_char_pointer psz, enum_dialog_result edialogresult) :
   m_strLabel(scopedstr),
   m_edialogresult(edialogresult)
{

   m_bTextRect = false;
   m_bPress = false;
   m_bHover = false;

}


xcb_button::~xcb_button()
{

}

