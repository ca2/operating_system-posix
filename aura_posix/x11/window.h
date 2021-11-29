//
// Created by camilo on 04/05/2021 20:58 BRT <3ThomasBS_!!
//
#pragma once


namespace windowing_posix
{


   class window :
      virtual public ::windowing::window
   {
   public:


#if defined(WITH_X11)


      __pointer(::xim::keyboard) m_pximkeyboard;


#endif


      window();
      virtual ~window();


   };


} // namespace windowing_posix



