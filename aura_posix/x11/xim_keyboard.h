//
// Created by camilo on 02/05/2021. 09:46 BRT <3ThomasBS_!!
//
#pragma once


//#include "acme/primitive/primitive/matter.h"


#if defined(LINUX)
// apt install libx11-dev
#include <X11/XKBlib.h>
#elif defined(FREEBSD)
#include <X11/Xlib.h>
#else
#error "Not supported operating system???"
#endif


namespace xim
{


   class keyboard :
      virtual public matter
   {
   public:


      bool        m_bXim;
      XIMStyle    m_imstyleBest;
      bool        m_bXic;
      XIC         m_xic;
      XIM         m_xim;
      Display *   m_pdisplay;
      Window      m_window;


      keyboard(Display * pdisplay, Window window);


      string get_key_press_text(XKeyPressedEvent * pevent, KeySym * pkeysym);


   };


} // namespac xim



