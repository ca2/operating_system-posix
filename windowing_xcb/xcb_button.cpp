#include "framework.h"
#include "_xcb.h"


xcb_button::xcb_button(const char * psz, enum_dialog_result edialogresult) :
   m_strLabel(psz),
   m_edialogresult(edialogresult)
{

   m_bTextRect = false;
   m_bPress = false;
   m_bHover = false;

}


xcb_button::~xcb_button()
{

}

