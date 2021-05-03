//
// Created by camilo on 02/05/2021. 09:46 BRT <3ThomasBS_!!
//
#pragma once


namespace xim
{


   class keyboard
   {
   public:


      bool  m_bXim;
      bool m_bBestStyle;
      bool m_bXic;
      XIC m_xic;
      XIM m_xim;


      keyboard();


      string get_key_press_text(Display * pdisplay, int code, int state);


   };


} // namespac xim



